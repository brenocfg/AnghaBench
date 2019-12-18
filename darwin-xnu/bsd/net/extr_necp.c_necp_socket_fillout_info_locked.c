#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct socket {int so_flags; int /*<<< orphan*/  so_cred; int /*<<< orphan*/  last_uuid; int /*<<< orphan*/  e_uuid; int /*<<< orphan*/  so_traffic_class; int /*<<< orphan*/  last_pid; int /*<<< orphan*/  e_pid; } ;
struct sockaddr_in6 {int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; void* sin6_family; } ;
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; void* sin_family; } ;
struct sockaddr {int sa_len; } ;
struct necp_uuid_id_mapping {int /*<<< orphan*/  id; } ;
struct necp_string_id_mapping {int /*<<< orphan*/  id; } ;
struct necp_socket_info {scalar_t__ cred_result; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; scalar_t__ bound_interface_index; int /*<<< orphan*/  domain; int /*<<< orphan*/  account_id; int /*<<< orphan*/  real_application_id; int /*<<< orphan*/  application_id; scalar_t__ protocol; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  uid; int /*<<< orphan*/  pid; } ;
struct TYPE_3__ {int /*<<< orphan*/  inp_domain; int /*<<< orphan*/ * inp_account; } ;
struct inpcb {int inp_flags2; int inp_flags; int inp_vflag; struct sockaddr in6p_faddr; int /*<<< orphan*/  inp_fport; struct sockaddr in6p_laddr; int /*<<< orphan*/  inp_lport; struct sockaddr inp_faddr; struct sockaddr inp_laddr; TYPE_2__* inp_boundifp; TYPE_1__ inp_necp_attributes; scalar_t__ inp_ip_p; struct socket* inp_socket; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct TYPE_4__ {scalar_t__ if_index; } ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_INET6 ; 
 int INP2_WANT_APP_POLICY ; 
 int INP_BOUND_IF ; 
 int INP_IPV4 ; 
 int INP_IPV6 ; 
 int NECP_KERNEL_ADDRESS_TYPE_CONDITIONS ; 
 int NECP_KERNEL_CONDITION_ACCOUNT_ID ; 
 int NECP_KERNEL_CONDITION_APP_ID ; 
 int NECP_KERNEL_CONDITION_DOMAIN ; 
 int NECP_KERNEL_CONDITION_ENTITLEMENT ; 
 int NECP_KERNEL_CONDITION_PID ; 
 int NECP_KERNEL_CONDITION_PROTOCOL ; 
 int NECP_KERNEL_CONDITION_REAL_APP_ID ; 
 int NECP_KERNEL_CONDITION_TRAFFIC_CLASS ; 
 int NECP_KERNEL_CONDITION_UID ; 
 int /*<<< orphan*/  PRIV_NET_PRIVILEGED_NECP_MATCH ; 
 scalar_t__ SOCK_PROTO (struct socket*) ; 
 int SOF_DELEGATED ; 
 int /*<<< orphan*/  kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,int) ; 
 int /*<<< orphan*/  memset (struct necp_socket_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  necp_account_id_list ; 
 int /*<<< orphan*/  necp_get_parent_cred_result (int /*<<< orphan*/ *,struct necp_socket_info*) ; 
 int necp_kernel_socket_policies_condition_mask ; 
 struct necp_string_id_mapping* necp_lookup_string_to_id_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct necp_uuid_id_mapping* necp_uuid_lookup_app_id_locked (int /*<<< orphan*/ ) ; 
 scalar_t__ priv_check_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
necp_socket_fillout_info_locked(struct inpcb *inp, struct sockaddr *override_local_addr, struct sockaddr *override_remote_addr, u_int32_t override_bound_interface, struct necp_socket_info *info)
{
	struct socket *so = NULL;

	memset(info, 0, sizeof(struct necp_socket_info));

	so = inp->inp_socket;

	if (necp_kernel_socket_policies_condition_mask & NECP_KERNEL_CONDITION_PID) {
		info->pid = ((so->so_flags & SOF_DELEGATED) ? so->e_pid : so->last_pid);
	}

	if (necp_kernel_socket_policies_condition_mask & NECP_KERNEL_CONDITION_UID) {
		info->uid = kauth_cred_getuid(so->so_cred);
	}

	if (necp_kernel_socket_policies_condition_mask & NECP_KERNEL_CONDITION_TRAFFIC_CLASS) {
		info->traffic_class = so->so_traffic_class;
	}

	if (necp_kernel_socket_policies_condition_mask & NECP_KERNEL_CONDITION_PROTOCOL) {
		if (inp->inp_ip_p) {
			info->protocol = inp->inp_ip_p;
		} else {
			info->protocol = SOCK_PROTO(so);
		}
	}

	if (inp->inp_flags2 & INP2_WANT_APP_POLICY && necp_kernel_socket_policies_condition_mask & NECP_KERNEL_CONDITION_APP_ID) {
		struct necp_uuid_id_mapping *existing_mapping = necp_uuid_lookup_app_id_locked(((so->so_flags & SOF_DELEGATED) ? so->e_uuid : so->last_uuid));
		if (existing_mapping) {
			info->application_id = existing_mapping->id;
		}

		if (!(so->so_flags & SOF_DELEGATED)) {
			info->real_application_id = info->application_id;
		} else if (necp_kernel_socket_policies_condition_mask & NECP_KERNEL_CONDITION_REAL_APP_ID) {
			struct necp_uuid_id_mapping *real_existing_mapping = necp_uuid_lookup_app_id_locked(so->last_uuid);
			if (real_existing_mapping) {
				info->real_application_id = real_existing_mapping->id;
			}
		}

		if (necp_kernel_socket_policies_condition_mask & NECP_KERNEL_CONDITION_ENTITLEMENT) {
			info->cred_result = priv_check_cred(so->so_cred, PRIV_NET_PRIVILEGED_NECP_MATCH, 0);
			if (info->cred_result != 0) {
				// Process does not have entitlement, check the parent process
				necp_get_parent_cred_result(NULL, info);
			}
		}
	}

	if (necp_kernel_socket_policies_condition_mask & NECP_KERNEL_CONDITION_ACCOUNT_ID && inp->inp_necp_attributes.inp_account != NULL) {
		struct necp_string_id_mapping *existing_mapping = necp_lookup_string_to_id_locked(&necp_account_id_list, inp->inp_necp_attributes.inp_account);
		if (existing_mapping) {
			info->account_id = existing_mapping->id;
		}
	}

	if (necp_kernel_socket_policies_condition_mask & NECP_KERNEL_CONDITION_DOMAIN) {
		info->domain = inp->inp_necp_attributes.inp_domain;
	}

	if (override_bound_interface) {
		info->bound_interface_index = override_bound_interface;
	} else {
		if ((inp->inp_flags & INP_BOUND_IF) && inp->inp_boundifp) {
			info->bound_interface_index = inp->inp_boundifp->if_index;
		}
	}

	if (necp_kernel_socket_policies_condition_mask & NECP_KERNEL_ADDRESS_TYPE_CONDITIONS) {
		if (inp->inp_vflag & INP_IPV4) {
			if (override_local_addr) {
				if (override_local_addr->sa_len <= sizeof(struct sockaddr_in)) {
					memcpy(&info->local_addr, override_local_addr, override_local_addr->sa_len);
				}
			} else {
				((struct sockaddr_in *)&info->local_addr)->sin_family = AF_INET;
				((struct sockaddr_in *)&info->local_addr)->sin_len = sizeof(struct sockaddr_in);
				((struct sockaddr_in *)&info->local_addr)->sin_port = inp->inp_lport;
				memcpy(&((struct sockaddr_in *)&info->local_addr)->sin_addr, &inp->inp_laddr, sizeof(struct in_addr));
			}

			if (override_remote_addr) {
				if (override_remote_addr->sa_len <= sizeof(struct sockaddr_in)) {
					memcpy(&info->remote_addr, override_remote_addr, override_remote_addr->sa_len);
				}
			} else {
				((struct sockaddr_in *)&info->remote_addr)->sin_family = AF_INET;
				((struct sockaddr_in *)&info->remote_addr)->sin_len = sizeof(struct sockaddr_in);
				((struct sockaddr_in *)&info->remote_addr)->sin_port = inp->inp_fport;
				memcpy(&((struct sockaddr_in *)&info->remote_addr)->sin_addr, &inp->inp_faddr, sizeof(struct in_addr));
			}
		} else if (inp->inp_vflag & INP_IPV6) {
			if (override_local_addr) {
				if (override_local_addr->sa_len <= sizeof(struct sockaddr_in6)) {
					memcpy(&info->local_addr, override_local_addr, override_local_addr->sa_len);
				}
			} else {
				((struct sockaddr_in6 *)&info->local_addr)->sin6_family = AF_INET6;
				((struct sockaddr_in6 *)&info->local_addr)->sin6_len = sizeof(struct sockaddr_in6);
				((struct sockaddr_in6 *)&info->local_addr)->sin6_port = inp->inp_lport;
				memcpy(&((struct sockaddr_in6 *)&info->local_addr)->sin6_addr, &inp->in6p_laddr, sizeof(struct in6_addr));
			}

			if (override_remote_addr) {
				if (override_remote_addr->sa_len <= sizeof(struct sockaddr_in6)) {
					memcpy(&info->remote_addr, override_remote_addr, override_remote_addr->sa_len);
				}
			} else {
				((struct sockaddr_in6 *)&info->remote_addr)->sin6_family = AF_INET6;
				((struct sockaddr_in6 *)&info->remote_addr)->sin6_len = sizeof(struct sockaddr_in6);
				((struct sockaddr_in6 *)&info->remote_addr)->sin6_port = inp->inp_fport;
				memcpy(&((struct sockaddr_in6 *)&info->remote_addr)->sin6_addr, &inp->in6p_faddr, sizeof(struct in6_addr));
			}
		}
	}
}