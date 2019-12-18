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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct socket {int dummy; } ;
struct content_filter {int cf_flags; int /*<<< orphan*/  cf_kcunit; int /*<<< orphan*/  cf_kcref; } ;
struct TYPE_8__ {int cfm_len; int /*<<< orphan*/  cfm_sock_id; int /*<<< orphan*/  cfm_op; int /*<<< orphan*/  cfm_type; int /*<<< orphan*/  cfm_version; } ;
struct TYPE_7__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct cfil_msg_sock_closed {TYPE_3__ cfc_msghdr; int /*<<< orphan*/  cfc_op_list_ctr; int /*<<< orphan*/  cfc_op_list; int /*<<< orphan*/  cfc_op_time; TYPE_2__ cfc_first_event; } ;
struct TYPE_10__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct cfil_info {TYPE_5__ cfi_first_event; int /*<<< orphan*/  cfi_op_list_ctr; int /*<<< orphan*/  cfi_op_list; int /*<<< orphan*/  cfi_op_time; struct cfil_entry* cfi_entries; } ;
struct cfil_entry {int cfe_flags; struct content_filter* cfe_filter; TYPE_1__* cfe_cfil_info; int /*<<< orphan*/  cfe_last_event; } ;
typedef  scalar_t__ errno_t ;
struct TYPE_9__ {int /*<<< orphan*/  cfs_closed_event_fail; int /*<<< orphan*/  cfs_closed_event_flow_control; int /*<<< orphan*/  cfs_closed_event_ok; } ;
struct TYPE_6__ {int /*<<< orphan*/  cfi_sock_id; } ;

/* Variables and functions */
 int CFEF_FLOW_CONTROLLED ; 
 int CFEF_SENT_SOCK_ATTACHED ; 
 int CFEF_SENT_SOCK_CLOSED ; 
 int CFF_FLOW_CONTROLLED ; 
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  CFI_ADD_TIME_LOG (struct cfil_info*,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int CFI_MAX_TIME_LOG_ENTRY ; 
 int /*<<< orphan*/  CFM_OP_SOCKET_CLOSED ; 
 int /*<<< orphan*/  CFM_TYPE_EVENT ; 
 int /*<<< orphan*/  CFM_VERSION_CURRENT ; 
 int /*<<< orphan*/  CTL_DATA_EOR ; 
 scalar_t__ ENOBUFS ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 int /*<<< orphan*/  bzero (struct cfil_msg_sock_closed*,int) ; 
 int /*<<< orphan*/  cfil_lck_rw ; 
 int /*<<< orphan*/  cfil_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_rw_lock_shared_to_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_rw_unlock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_rw_unlock_shared (int /*<<< orphan*/ *) ; 
 TYPE_4__ cfil_stats ; 
 scalar_t__ ctl_enqueuedata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfil_msg_sock_closed*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  microuptime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 

int
cfil_dispatch_closed_event(struct socket *so, struct cfil_info *cfil_info, int kcunit)
{
	struct cfil_entry *entry;
	struct cfil_msg_sock_closed msg_closed;
	errno_t error = 0;
	struct content_filter *cfc;

	socket_lock_assert_owned(so);

	cfil_rw_lock_shared(&cfil_lck_rw);

	entry = &cfil_info->cfi_entries[kcunit - 1];
	cfc = entry->cfe_filter;
	if (cfc == NULL)
		goto done;

	CFIL_LOG(LOG_INFO, "so %llx kcunit %d",
			 (uint64_t)VM_KERNEL_ADDRPERM(so), kcunit);

	/* Would be wasteful to try when flow controlled */
	if (cfc->cf_flags & CFF_FLOW_CONTROLLED) {
		error = ENOBUFS;
		goto done;
	}
	/*
	 * Send a single closed message per filter
	 */
	if ((entry->cfe_flags & CFEF_SENT_SOCK_CLOSED) != 0)
		goto done;
	if ((entry->cfe_flags & CFEF_SENT_SOCK_ATTACHED) == 0)
		goto done;

	microuptime(&entry->cfe_last_event);
	CFI_ADD_TIME_LOG(cfil_info, &entry->cfe_last_event, &cfil_info->cfi_first_event, CFM_OP_SOCKET_CLOSED);

	bzero(&msg_closed, sizeof(struct cfil_msg_sock_closed));
	msg_closed.cfc_msghdr.cfm_len = sizeof(struct cfil_msg_sock_closed);
	msg_closed.cfc_msghdr.cfm_version = CFM_VERSION_CURRENT;
	msg_closed.cfc_msghdr.cfm_type = CFM_TYPE_EVENT;
	msg_closed.cfc_msghdr.cfm_op = CFM_OP_SOCKET_CLOSED;
	msg_closed.cfc_msghdr.cfm_sock_id = entry->cfe_cfil_info->cfi_sock_id;
	msg_closed.cfc_first_event.tv_sec = cfil_info->cfi_first_event.tv_sec;
	msg_closed.cfc_first_event.tv_usec = cfil_info->cfi_first_event.tv_usec;
	memcpy(msg_closed.cfc_op_time, cfil_info->cfi_op_time, sizeof(uint32_t)*CFI_MAX_TIME_LOG_ENTRY);
	memcpy(msg_closed.cfc_op_list, cfil_info->cfi_op_list, sizeof(unsigned char)*CFI_MAX_TIME_LOG_ENTRY);
	msg_closed.cfc_op_list_ctr = cfil_info->cfi_op_list_ctr;

#if LIFECYCLE_DEBUG
	CFIL_LOG(LOG_ERR, "CFIL: LIFECYCLE: SENDING CLOSED UP: <sock id %llu> op ctr %d, start time %llu.%llu", msg_closed.cfc_msghdr.cfm_sock_id, cfil_info->cfi_op_list_ctr, cfil_info->cfi_first_event.tv_sec, cfil_info->cfi_first_event.tv_usec);
#endif
	/* for debugging
	if (msg_closed.cfc_op_list_ctr > CFI_MAX_TIME_LOG_ENTRY) {
		msg_closed.cfc_op_list_ctr  = CFI_MAX_TIME_LOG_ENTRY;       // just in case
	}
	for (unsigned int i = 0; i < msg_closed.cfc_op_list_ctr ; i++) {
		CFIL_LOG(LOG_ERR, "MD: socket %llu event %2u, time + %u msec", msg_closed.cfc_msghdr.cfm_sock_id, (unsigned short)msg_closed.cfc_op_list[i], msg_closed.cfc_op_time[i]);
	}
	*/

	error = ctl_enqueuedata(entry->cfe_filter->cf_kcref,
				entry->cfe_filter->cf_kcunit,
				&msg_closed,
				sizeof(struct cfil_msg_sock_closed),
				CTL_DATA_EOR);
	if (error != 0) {
		CFIL_LOG(LOG_ERR, "ctl_enqueuedata() failed: %d",
			error);
		goto done;
	}

	entry->cfe_flags |= CFEF_SENT_SOCK_CLOSED;
	OSIncrementAtomic(&cfil_stats.cfs_closed_event_ok);
done:
	/* We can recover from flow control */
	if (error == ENOBUFS) {
		entry->cfe_flags |= CFEF_FLOW_CONTROLLED;
		OSIncrementAtomic(&cfil_stats.cfs_closed_event_flow_control);

		if (!cfil_rw_lock_shared_to_exclusive(&cfil_lck_rw))
			cfil_rw_lock_exclusive(&cfil_lck_rw);

		cfc->cf_flags |= CFF_FLOW_CONTROLLED;

		cfil_rw_unlock_exclusive(&cfil_lck_rw);
	} else {
		if (error != 0)
			OSIncrementAtomic(&cfil_stats.cfs_closed_event_fail);

		cfil_rw_unlock_shared(&cfil_lck_rw);
	}

	return (error);
}