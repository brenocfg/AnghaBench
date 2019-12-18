#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct socket {int so_flags; int /*<<< orphan*/  last_uuid; int /*<<< orphan*/  last_pid; int /*<<< orphan*/  e_uuid; int /*<<< orphan*/  e_pid; TYPE_3__* so_proto; } ;
struct content_filter {int cf_necp_control_unit; int cf_flags; int /*<<< orphan*/  cf_kcunit; int /*<<< orphan*/  cf_kcref; } ;
struct TYPE_8__ {int cfm_len; scalar_t__ cfm_sock_id; int /*<<< orphan*/  cfm_op; int /*<<< orphan*/  cfm_type; int /*<<< orphan*/  cfm_version; } ;
struct cfil_msg_sock_attached {int /*<<< orphan*/  cfs_e_uuid; int /*<<< orphan*/  cfs_e_pid; int /*<<< orphan*/  cfs_uuid; int /*<<< orphan*/  cfs_pid; int /*<<< orphan*/  cfs_sock_protocol; int /*<<< orphan*/  cfs_sock_type; int /*<<< orphan*/  cfs_sock_family; TYPE_1__ cfs_msghdr; } ;
struct TYPE_12__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct cfil_info {TYPE_5__ cfi_first_event; struct cfil_entry* cfi_entries; } ;
struct TYPE_13__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct cfil_entry {int cfe_flags; TYPE_6__ cfe_last_event; struct content_filter* cfe_filter; TYPE_4__* cfe_cfil_info; } ;
typedef  scalar_t__ errno_t ;
struct TYPE_14__ {int /*<<< orphan*/  cfs_attach_event_fail; int /*<<< orphan*/  cfs_attach_event_flow_control; int /*<<< orphan*/  cfs_attach_event_ok; } ;
struct TYPE_11__ {scalar_t__ cfi_sock_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  pr_protocol; int /*<<< orphan*/  pr_type; TYPE_2__* pr_domain; } ;
struct TYPE_9__ {int /*<<< orphan*/  dom_family; } ;

/* Variables and functions */
 int CFEF_FLOW_CONTROLLED ; 
 int CFEF_SENT_SOCK_ATTACHED ; 
 int CFF_FLOW_CONTROLLED ; 
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  CFM_OP_SOCKET_ATTACHED ; 
 int /*<<< orphan*/  CFM_TYPE_EVENT ; 
 int /*<<< orphan*/  CFM_VERSION_CURRENT ; 
 int /*<<< orphan*/  CTL_DATA_EOR ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOBUFS ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int MAX_CONTENT_FILTER ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 int SOF_DELEGATED ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 int /*<<< orphan*/  bzero (struct cfil_msg_sock_attached*,int) ; 
 int /*<<< orphan*/  cfil_lck_rw ; 
 int /*<<< orphan*/  cfil_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_rw_lock_shared_to_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_rw_unlock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_rw_unlock_shared (int /*<<< orphan*/ *) ; 
 TYPE_7__ cfil_stats ; 
 struct content_filter** content_filters ; 
 scalar_t__ ctl_enqueuedata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfil_msg_sock_attached*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  microuptime (TYPE_6__*) ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 

__attribute__((used)) static int
cfil_dispatch_attach_event(struct socket *so, struct cfil_info *cfil_info, uint32_t filter_control_unit)
{
	errno_t error = 0;
	struct cfil_entry *entry = NULL;
	struct cfil_msg_sock_attached msg_attached;
	uint32_t kcunit;
	struct content_filter *cfc = NULL;

	socket_lock_assert_owned(so);

	cfil_rw_lock_shared(&cfil_lck_rw);

	if (so->so_proto == NULL || so->so_proto->pr_domain == NULL) {
		error = EINVAL;
		goto done;
	}
	/*
	 * Find the matching filter unit
	 */
	for (kcunit = 1; kcunit <= MAX_CONTENT_FILTER; kcunit++) {
		cfc = content_filters[kcunit - 1];

		if (cfc == NULL)
			continue;
		if (cfc->cf_necp_control_unit != filter_control_unit)
			continue;
		entry = &cfil_info->cfi_entries[kcunit - 1];
		if (entry->cfe_filter == NULL)
			continue;

		VERIFY(cfc == entry->cfe_filter);

		break;
	}

	if (entry == NULL || entry->cfe_filter == NULL)
		goto done;

	if ((entry->cfe_flags & CFEF_SENT_SOCK_ATTACHED))
		goto done;

	CFIL_LOG(LOG_INFO, "so %llx filter_control_unit %u kcunit %u",
		(uint64_t)VM_KERNEL_ADDRPERM(so), filter_control_unit, kcunit);

	/* Would be wasteful to try when flow controlled */
	if (cfc->cf_flags & CFF_FLOW_CONTROLLED) {
		error = ENOBUFS;
		goto done;
	}

	bzero(&msg_attached, sizeof(struct cfil_msg_sock_attached));
	msg_attached.cfs_msghdr.cfm_len = sizeof(struct cfil_msg_sock_attached);
	msg_attached.cfs_msghdr.cfm_version = CFM_VERSION_CURRENT;
	msg_attached.cfs_msghdr.cfm_type = CFM_TYPE_EVENT;
	msg_attached.cfs_msghdr.cfm_op = CFM_OP_SOCKET_ATTACHED;
	msg_attached.cfs_msghdr.cfm_sock_id = entry->cfe_cfil_info->cfi_sock_id;

	msg_attached.cfs_sock_family = so->so_proto->pr_domain->dom_family;
	msg_attached.cfs_sock_type = so->so_proto->pr_type;
	msg_attached.cfs_sock_protocol = so->so_proto->pr_protocol;
	msg_attached.cfs_pid = so->last_pid;
	memcpy(msg_attached.cfs_uuid, so->last_uuid, sizeof(uuid_t));
	if (so->so_flags & SOF_DELEGATED) {
		msg_attached.cfs_e_pid = so->e_pid;
		memcpy(msg_attached.cfs_e_uuid, so->e_uuid, sizeof(uuid_t));
	} else {
		msg_attached.cfs_e_pid = so->last_pid;
		memcpy(msg_attached.cfs_e_uuid, so->last_uuid, sizeof(uuid_t));
	}

#if LIFECYCLE_DEBUG
	CFIL_LOG(LOG_DEBUG, "CFIL: LIFECYCLE: SENDING ATTACH UP <sockID %llu> ",
			 entry->cfe_cfil_info->cfi_sock_id);
#endif

	error = ctl_enqueuedata(entry->cfe_filter->cf_kcref,
				entry->cfe_filter->cf_kcunit,
				&msg_attached,
				sizeof(struct cfil_msg_sock_attached),
				CTL_DATA_EOR);
	if (error != 0) {
		CFIL_LOG(LOG_ERR, "ctl_enqueuedata() failed: %d", error);
		goto done;
	}
	microuptime(&entry->cfe_last_event);
	cfil_info->cfi_first_event.tv_sec = entry->cfe_last_event.tv_sec;
	cfil_info->cfi_first_event.tv_usec = entry->cfe_last_event.tv_usec;

	entry->cfe_flags |= CFEF_SENT_SOCK_ATTACHED;
	OSIncrementAtomic(&cfil_stats.cfs_attach_event_ok);
done:

	/* We can recover from flow control */
	if (error == ENOBUFS) {
		entry->cfe_flags |= CFEF_FLOW_CONTROLLED;
		OSIncrementAtomic(&cfil_stats.cfs_attach_event_flow_control);

		if (!cfil_rw_lock_shared_to_exclusive(&cfil_lck_rw))
			cfil_rw_lock_exclusive(&cfil_lck_rw);

		cfc->cf_flags |= CFF_FLOW_CONTROLLED;

		cfil_rw_unlock_exclusive(&cfil_lck_rw);
	} else {
		if (error != 0)
			OSIncrementAtomic(&cfil_stats.cfs_attach_event_fail);

		cfil_rw_unlock_shared(&cfil_lck_rw);
	}
	return (error);
}