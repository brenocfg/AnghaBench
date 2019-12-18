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
struct socket {int /*<<< orphan*/  so_flags1; struct cfil_info* so_cfil; int /*<<< orphan*/ * so_cfil_db; } ;
struct cfil_msg_hdr {int /*<<< orphan*/  cfm_sock_id; } ;
struct cfil_msg_bless_client {int /*<<< orphan*/  cfb_client_uuid; } ;
struct cfil_info {int /*<<< orphan*/  cfi_sock_id; scalar_t__ cfi_hash_entry; } ;
typedef  int errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFM_MAX_OFFSET ; 
 int ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SOF1_CONTENT_FILTER_SKIP ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 int /*<<< orphan*/  cfil_action_data_pass (struct socket*,struct cfil_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cfil_info* cfil_db_get_cfil_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct socket* cfil_socket_from_client_uuid (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 

int
cfil_action_bless_client(uint32_t kcunit, struct cfil_msg_hdr *msghdr)
{
	errno_t error = 0;
	struct cfil_info *cfil_info = NULL;

	bool cfil_attached = false;
	struct cfil_msg_bless_client *blessmsg = (struct cfil_msg_bless_client *)msghdr;

	// Search and lock socket
	struct socket *so = cfil_socket_from_client_uuid(blessmsg->cfb_client_uuid, &cfil_attached);
	if (so == NULL) {
		error = ENOENT;
	} else {
		// The client gets a pass automatically
		cfil_info = (so->so_cfil_db != NULL) ?
			cfil_db_get_cfil_info(so->so_cfil_db, msghdr->cfm_sock_id) : so->so_cfil;

		if (cfil_attached) {
#if VERDICT_DEBUG
			if (cfil_info != NULL) {
				CFIL_LOG(LOG_ERR, "CFIL: VERDICT RECEIVED: BLESS %s <so %llx sockID %llu>",
						 cfil_info->cfi_hash_entry ? "UDP" : "TCP",
						 (uint64_t)VM_KERNEL_ADDRPERM(so),
						 cfil_info->cfi_sock_id);
			}
#endif
			(void)cfil_action_data_pass(so, cfil_info, kcunit, 1, CFM_MAX_OFFSET, CFM_MAX_OFFSET);
			(void)cfil_action_data_pass(so, cfil_info, kcunit, 0, CFM_MAX_OFFSET, CFM_MAX_OFFSET);
		} else {
			so->so_flags1 |= SOF1_CONTENT_FILTER_SKIP;
		}
		socket_unlock(so, 1);
	}

	return (error);
}