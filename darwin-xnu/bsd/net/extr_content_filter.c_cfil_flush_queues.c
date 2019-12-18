#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct socket {int so_flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  cfi_inject_q; } ;
struct TYPE_7__ {int /*<<< orphan*/  cfi_inject_q; } ;
struct cfil_info {int cfi_flags; TYPE_4__ cfi_rcv; struct cfil_entry* cfi_entries; TYPE_2__ cfi_snd; } ;
struct TYPE_8__ {int /*<<< orphan*/  cfe_pending_q; int /*<<< orphan*/  cfe_ctl_q; } ;
struct TYPE_6__ {int /*<<< orphan*/  cfe_pending_q; int /*<<< orphan*/  cfe_ctl_q; } ;
struct cfil_entry {TYPE_3__ cfe_rcv; TYPE_1__ cfe_snd; } ;
struct TYPE_10__ {int /*<<< orphan*/  cfs_flush_in_close; int /*<<< orphan*/  cfs_flush_in_drop; int /*<<< orphan*/  cfs_flush_out_close; int /*<<< orphan*/  cfs_flush_out_drop; } ;

/* Variables and functions */
 int CFIF_DROP ; 
 int /*<<< orphan*/  CFIL_INFO_VERIFY (struct cfil_info*) ; 
 int MAX_CONTENT_FILTER ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 int SOF_CONTENT_FILTER ; 
 int /*<<< orphan*/  cfil_acquire_sockbuf (struct socket*,struct cfil_info*,int) ; 
 scalar_t__ cfil_queue_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_release_sockbuf (struct socket*,int) ; 
 TYPE_5__ cfil_stats ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 

__attribute__((used)) static void
cfil_flush_queues(struct socket *so, struct cfil_info *cfil_info)
{
	struct cfil_entry *entry;
	int kcunit;
	uint64_t drained;

	if ((so->so_flags & SOF_CONTENT_FILTER) == 0 || cfil_info == NULL)
		goto done;

	socket_lock_assert_owned(so);

	/*
	 * Flush the output queues and ignore errors as long as
	 * we are attached
	 */
	(void) cfil_acquire_sockbuf(so, cfil_info, 1);
	if (cfil_info != NULL) {
		drained = 0;
		for (kcunit = 1; kcunit <= MAX_CONTENT_FILTER; kcunit++) {
			entry = &cfil_info->cfi_entries[kcunit - 1];

			drained += cfil_queue_drain(&entry->cfe_snd.cfe_ctl_q);
			drained += cfil_queue_drain(&entry->cfe_snd.cfe_pending_q);
		}
		drained += cfil_queue_drain(&cfil_info->cfi_snd.cfi_inject_q);

		if (drained) {
			if (cfil_info->cfi_flags & CFIF_DROP)
				OSIncrementAtomic(
					&cfil_stats.cfs_flush_out_drop);
			else
				OSIncrementAtomic(
					&cfil_stats.cfs_flush_out_close);
		}
	}
	cfil_release_sockbuf(so, 1);

	/*
	 * Flush the input queues
	 */
	(void) cfil_acquire_sockbuf(so, cfil_info, 0);
	if (cfil_info != NULL) {
		drained = 0;
		for (kcunit = 1; kcunit <= MAX_CONTENT_FILTER; kcunit++) {
			entry = &cfil_info->cfi_entries[kcunit - 1];

				drained += cfil_queue_drain(
					&entry->cfe_rcv.cfe_ctl_q);
				drained += cfil_queue_drain(
					&entry->cfe_rcv.cfe_pending_q);
		}
		drained += cfil_queue_drain(&cfil_info->cfi_rcv.cfi_inject_q);

		if (drained) {
			if (cfil_info->cfi_flags & CFIF_DROP)
				OSIncrementAtomic(
					&cfil_stats.cfs_flush_in_drop);
			else
				OSIncrementAtomic(
					&cfil_stats.cfs_flush_in_close);
		}
	}
	cfil_release_sockbuf(so, 0);
done:
	CFIL_INFO_VERIFY(cfil_info);
}