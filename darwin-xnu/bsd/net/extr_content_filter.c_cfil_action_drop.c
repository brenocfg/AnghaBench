#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct socket {int so_flags; int /*<<< orphan*/ * so_cfil_db; } ;
struct proc {int dummy; } ;
struct cfil_info {int cfi_flags; struct cfil_entry* cfi_entries; } ;
struct cfil_entry {int /*<<< orphan*/  cfe_flags; int /*<<< orphan*/ * cfe_filter; } ;
typedef  scalar_t__ errno_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFEF_CFIL_DETACHED ; 
 int CFIF_CLOSE_WAIT ; 
 int CFIF_DROP ; 
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int SHUTDOWN_SOCKET_LEVEL_CONTENT_FILTER ; 
 int SHUTDOWN_SOCKET_LEVEL_DISCONNECT_ALL ; 
 int SOF_CONTENT_FILTER ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 scalar_t__ cfil_filters_attached (struct socket*) ; 
 int /*<<< orphan*/  cfil_flush_queues (struct socket*,struct cfil_info*) ; 
 int /*<<< orphan*/  cfil_info_log (int /*<<< orphan*/ ,struct cfil_info*,char*) ; 
 struct proc* current_proc () ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 
 scalar_t__ sodefunct (struct proc*,struct socket*,int) ; 
 scalar_t__ sosetdefunct (struct proc*,struct socket*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

int
cfil_action_drop(struct socket *so, struct cfil_info *cfil_info, uint32_t kcunit)
{
	errno_t error = 0;
	struct cfil_entry *entry;
	struct proc *p;

	if ((so->so_flags & SOF_CONTENT_FILTER) == 0 || cfil_info == NULL)
		goto done;

	socket_lock_assert_owned(so);

	entry = &cfil_info->cfi_entries[kcunit - 1];

	/* Are we attached to the filter? */
	if (entry->cfe_filter == NULL)
		goto done;

	cfil_info->cfi_flags |= CFIF_DROP;

	p = current_proc();

	/*
	 * Force the socket to be marked defunct
	 * (forcing fixed along with rdar://19391339)
	 */
	if (so->so_cfil_db == NULL) {
		error = sosetdefunct(p, so,
							 SHUTDOWN_SOCKET_LEVEL_CONTENT_FILTER | SHUTDOWN_SOCKET_LEVEL_DISCONNECT_ALL,
							 FALSE);

		/* Flush the socket buffer and disconnect */
		if (error == 0)
			error = sodefunct(p, so,
							  SHUTDOWN_SOCKET_LEVEL_CONTENT_FILTER | SHUTDOWN_SOCKET_LEVEL_DISCONNECT_ALL);
	}

	/* The filter is done, mark as detached */
	entry->cfe_flags |= CFEF_CFIL_DETACHED;
#if LIFECYCLE_DEBUG
	cfil_info_log(LOG_ERR, cfil_info, "CFIL: LIFECYCLE: DROP - DETACH");
#endif
	CFIL_LOG(LOG_INFO, "so %llx detached %u",
		(uint64_t)VM_KERNEL_ADDRPERM(so), kcunit);

	/* Pending data needs to go */
	cfil_flush_queues(so, cfil_info);

	if (cfil_info && (cfil_info->cfi_flags & CFIF_CLOSE_WAIT)) {
		if (cfil_filters_attached(so) == 0) {
			CFIL_LOG(LOG_INFO, "so %llx waking",
				(uint64_t)VM_KERNEL_ADDRPERM(so));
			wakeup((caddr_t)cfil_info);
		}
	}
done:
	return (error);
}