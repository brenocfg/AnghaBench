#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int u_int32_t ;
struct socket {struct cfil_info* so_cfil; int /*<<< orphan*/ * so_cfil_db; } ;
typedef  void content_filter ;
struct cfil_msg_hdr {int cfm_op; int cfm_len; int cfm_sock_id; int /*<<< orphan*/  cfm_type; int /*<<< orphan*/  cfm_version; } ;
struct cfil_msg_bless_client {int dummy; } ;
struct cfil_msg_action {int /*<<< orphan*/  cfa_in_peek_offset; int /*<<< orphan*/  cfa_in_pass_offset; int /*<<< orphan*/  cfa_out_peek_offset; int /*<<< orphan*/  cfa_out_pass_offset; } ;
struct cfil_info {int cfi_flags; int /*<<< orphan*/  cfi_first_event; struct cfil_entry* cfi_entries; } ;
struct cfil_entry {int cfe_flags; int /*<<< orphan*/  cfe_last_action; int /*<<< orphan*/ * cfe_filter; } ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  kern_ctl_ref ;
typedef  scalar_t__ errno_t ;
struct TYPE_2__ {int /*<<< orphan*/  cfs_ctl_send_bad; int /*<<< orphan*/  cfs_ctl_send_ok; int /*<<< orphan*/  cfs_ctl_action_bad_len; int /*<<< orphan*/  cfs_ctl_action_bad_op; int /*<<< orphan*/  cfs_ctl_action_drop; int /*<<< orphan*/  cfs_ctl_action_data_update; } ;

/* Variables and functions */
 int CFEF_DATA_START ; 
 int CFEF_SENT_SOCK_ATTACHED ; 
 int CFIF_DROP ; 
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  CFI_ADD_TIME_LOG (struct cfil_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
#define  CFM_OP_BLESS_CLIENT 130 
#define  CFM_OP_DATA_UPDATE 129 
#define  CFM_OP_DROP 128 
 int /*<<< orphan*/  CFM_TYPE_ACTION ; 
 int /*<<< orphan*/  CFM_VERSION_CURRENT ; 
 scalar_t__ EINVAL ; 
 scalar_t__ EJUSTRETURN ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int MAX_CONTENT_FILTER ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 scalar_t__ cfil_action_bless_client (int,struct cfil_msg_hdr*) ; 
 scalar_t__ cfil_action_data_pass (struct socket*,struct cfil_info*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cfil_action_drop (struct socket*,struct cfil_info*,int) ; 
 struct cfil_info* cfil_db_get_cfil_info (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cfil_lck_rw ; 
 int /*<<< orphan*/  cfil_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_rw_unlock_shared (int /*<<< orphan*/ *) ; 
 struct socket* cfil_socket_from_sock_id (int,int) ; 
 TYPE_1__ cfil_stats ; 
 scalar_t__* content_filters ; 
 int m_length (int /*<<< orphan*/ ) ; 
 scalar_t__ mbuf_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_freem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  microuptime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 

__attribute__((used)) static errno_t
cfil_ctl_send(kern_ctl_ref kctlref, u_int32_t kcunit, void *unitinfo, mbuf_t m,
		int flags)
{
#pragma unused(kctlref, flags)
	errno_t	error = 0;
	struct cfil_msg_hdr *msghdr;
	struct content_filter *cfc = (struct content_filter *)unitinfo;
	struct socket *so;
	struct cfil_msg_action *action_msg;
	struct cfil_entry *entry;
	struct cfil_info *cfil_info = NULL;

	CFIL_LOG(LOG_INFO, "");

	if (content_filters == NULL) {
		CFIL_LOG(LOG_ERR, "no content filter");
		error = EINVAL;
		goto done;
	}
	if (kcunit > MAX_CONTENT_FILTER) {
		CFIL_LOG(LOG_ERR, "kcunit %u > MAX_CONTENT_FILTER (%d)",
			kcunit, MAX_CONTENT_FILTER);
		error = EINVAL;
		goto done;
	}

	if (m_length(m) < sizeof(struct cfil_msg_hdr)) {
		CFIL_LOG(LOG_ERR, "too short %u", m_length(m));
		error = EINVAL;
		goto done;
	}
	msghdr = (struct cfil_msg_hdr *)mbuf_data(m);
	if (msghdr->cfm_version != CFM_VERSION_CURRENT) {
		CFIL_LOG(LOG_ERR, "bad version %u", msghdr->cfm_version);
		error = EINVAL;
		goto done;
	}
	if (msghdr->cfm_type != CFM_TYPE_ACTION) {
		CFIL_LOG(LOG_ERR, "bad type %u", msghdr->cfm_type);
		error = EINVAL;
		goto done;
	}
	/* Validate action operation */
	switch (msghdr->cfm_op) {
		case CFM_OP_DATA_UPDATE:
			OSIncrementAtomic(
				&cfil_stats.cfs_ctl_action_data_update);
			break;
		case CFM_OP_DROP:
			OSIncrementAtomic(&cfil_stats.cfs_ctl_action_drop);
			break;
		case CFM_OP_BLESS_CLIENT:
			if (msghdr->cfm_len != sizeof(struct cfil_msg_bless_client)) {
				OSIncrementAtomic(&cfil_stats.cfs_ctl_action_bad_len);
				error = EINVAL;
				CFIL_LOG(LOG_ERR, "bad len: %u for op %u",
						 msghdr->cfm_len,
						 msghdr->cfm_op);
				goto done;
			}
			error = cfil_action_bless_client(kcunit, msghdr);
			goto done;
		default:
			OSIncrementAtomic(&cfil_stats.cfs_ctl_action_bad_op);
			CFIL_LOG(LOG_ERR, "bad op %u", msghdr->cfm_op);
			error = EINVAL;
			goto done;
		}
		if (msghdr->cfm_len != sizeof(struct cfil_msg_action)) {
			OSIncrementAtomic(&cfil_stats.cfs_ctl_action_bad_len);
				error = EINVAL;
				CFIL_LOG(LOG_ERR, "bad len: %u for op %u",
					msghdr->cfm_len,
					msghdr->cfm_op);
				goto done;
			}
	cfil_rw_lock_shared(&cfil_lck_rw);
	if (cfc != (void *)content_filters[kcunit - 1]) {
		CFIL_LOG(LOG_ERR, "unitinfo does not match for kcunit %u",
			kcunit);
		error = EINVAL;
		cfil_rw_unlock_shared(&cfil_lck_rw);
		goto done;
	}
	cfil_rw_unlock_shared(&cfil_lck_rw);

	// Search for socket (TCP+UDP and lock so)
	so = cfil_socket_from_sock_id(msghdr->cfm_sock_id, false);
	if (so == NULL) {
		CFIL_LOG(LOG_NOTICE, "bad sock_id %llx",
			msghdr->cfm_sock_id);
		error = EINVAL;
		goto done;
	}

	cfil_info = so->so_cfil_db != NULL ?
		cfil_db_get_cfil_info(so->so_cfil_db, msghdr->cfm_sock_id) : so->so_cfil;

	if (cfil_info == NULL) {
		CFIL_LOG(LOG_NOTICE, "so %llx <id %llu> not attached",
				 (uint64_t)VM_KERNEL_ADDRPERM(so), msghdr->cfm_sock_id);
		error = EINVAL;
		goto unlock;
	} else if (cfil_info->cfi_flags & CFIF_DROP) {
		CFIL_LOG(LOG_NOTICE, "so %llx drop set",
			(uint64_t)VM_KERNEL_ADDRPERM(so));
		error = EINVAL;
		goto unlock;
	}
	entry = &cfil_info->cfi_entries[kcunit - 1];
	if (entry->cfe_filter == NULL) {
		CFIL_LOG(LOG_NOTICE, "so %llx no filter",
			(uint64_t)VM_KERNEL_ADDRPERM(so));
		error = EINVAL;
		goto unlock;
	}

	if (entry->cfe_flags & CFEF_SENT_SOCK_ATTACHED)
		entry->cfe_flags |= CFEF_DATA_START;
	else {
		CFIL_LOG(LOG_ERR,
			"so %llx attached not sent for %u",
			(uint64_t)VM_KERNEL_ADDRPERM(so), kcunit);
		error = EINVAL;
		goto unlock;
	}

	microuptime(&entry->cfe_last_action);
	CFI_ADD_TIME_LOG(cfil_info, &entry->cfe_last_action, &cfil_info->cfi_first_event, msghdr->cfm_op);

	action_msg = (struct cfil_msg_action *)msghdr;

	switch (msghdr->cfm_op) {
		case CFM_OP_DATA_UPDATE:
#if VERDICT_DEBUG
			CFIL_LOG(LOG_ERR, "CFIL: VERDICT RECEIVED: <so %llx sockID %llu> <IN peek:%llu pass:%llu, OUT peek:%llu pass:%llu>",
					 (uint64_t)VM_KERNEL_ADDRPERM(so),
					 cfil_info->cfi_sock_id,
					 action_msg->cfa_in_peek_offset, action_msg->cfa_in_pass_offset,
					 action_msg->cfa_out_peek_offset, action_msg->cfa_out_pass_offset);
#endif
			if (action_msg->cfa_out_peek_offset != 0 ||
				action_msg->cfa_out_pass_offset != 0)
				error = cfil_action_data_pass(so, cfil_info, kcunit, 1,
					action_msg->cfa_out_pass_offset,
					action_msg->cfa_out_peek_offset);
			if (error == EJUSTRETURN)
				error = 0;
			if (error != 0)
				break;
			if (action_msg->cfa_in_peek_offset != 0 ||
				action_msg->cfa_in_pass_offset != 0)
				error = cfil_action_data_pass(so, cfil_info, kcunit, 0,
					action_msg->cfa_in_pass_offset,
					action_msg->cfa_in_peek_offset);
			if (error == EJUSTRETURN)
				error = 0;
			break;

		case CFM_OP_DROP:
			error = cfil_action_drop(so, cfil_info, kcunit);
			break;

		default:
			error = EINVAL;
			break;
	}
unlock:
	socket_unlock(so, 1);
done:
	mbuf_freem(m);

	if (error == 0)
		OSIncrementAtomic(&cfil_stats.cfs_ctl_send_ok);
	else
		OSIncrementAtomic(&cfil_stats.cfs_ctl_send_bad);

	return (error);
}