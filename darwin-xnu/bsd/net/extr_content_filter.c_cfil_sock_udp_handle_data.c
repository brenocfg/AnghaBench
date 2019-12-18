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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct mbuf {scalar_t__ m_type; } ;
struct cfil_info {int cfi_flags; } ;
struct cfil_hash_entry {struct cfil_info* cfentry_cfil; int /*<<< orphan*/  cfentry_lastused; } ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_2__ {int /*<<< orphan*/  cfs_data_in_oob; int /*<<< orphan*/  cfs_data_in_control; int /*<<< orphan*/  cfs_sock_userspace_only; int /*<<< orphan*/  cfs_sock_attach_in_vain; } ;

/* Variables and functions */
 int CFIF_DROP ; 
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ MT_OOBDATA ; 
 int NECP_MASK_USERSPACE_ONLY ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 scalar_t__ cfil_active_count ; 
 int /*<<< orphan*/  cfil_data_common (struct socket*,struct cfil_info*,int,struct sockaddr*,struct mbuf*,struct mbuf*,int) ; 
 int /*<<< orphan*/  cfil_hash_entry_log (int /*<<< orphan*/ ,struct socket*,struct cfil_hash_entry*,int /*<<< orphan*/ ,char*) ; 
 struct cfil_hash_entry* cfil_sock_udp_get_flow (struct socket*,int,int,struct sockaddr*,struct sockaddr*) ; 
 TYPE_1__ cfil_stats ; 
 int necp_socket_get_content_filter_control_unit (struct socket*) ; 
 int /*<<< orphan*/  net_uptime () ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 

errno_t
cfil_sock_udp_handle_data(bool outgoing, struct socket *so,
                          struct sockaddr *local, struct sockaddr *remote,
                          struct mbuf *data, struct mbuf *control, uint32_t flags)
{
#pragma unused(outgoing, so, local, remote, data, control, flags)
    errno_t error = 0;
    uint32_t filter_control_unit;
	struct cfil_hash_entry *hash_entry = NULL;
	struct cfil_info *cfil_info = NULL;

    socket_lock_assert_owned(so);

    if (cfil_active_count == 0) {
        CFIL_LOG(LOG_DEBUG, "CFIL: UDP no active filter");
        OSIncrementAtomic(&cfil_stats.cfs_sock_attach_in_vain);
        return (error);
    }
    
    filter_control_unit = necp_socket_get_content_filter_control_unit(so);
    if (filter_control_unit == 0) {
        CFIL_LOG(LOG_DEBUG, "CFIL: UDP failed to get control unit");
        return (error);
    }

    if ((filter_control_unit & NECP_MASK_USERSPACE_ONLY) != 0) {
        CFIL_LOG(LOG_DEBUG, "CFIL: UDP user space only");
        OSIncrementAtomic(&cfil_stats.cfs_sock_userspace_only);
        return (error);
    }
	
    hash_entry = cfil_sock_udp_get_flow(so, filter_control_unit, outgoing, local, remote);
    if (hash_entry == NULL || hash_entry->cfentry_cfil == NULL) {
		CFIL_LOG(LOG_ERR, "CFIL: Falied to create UDP flow");
        return (EPIPE);
    }
	// Update last used timestamp, this is for flow Idle TO
	hash_entry->cfentry_lastused = net_uptime();
	cfil_info = hash_entry->cfentry_cfil;

	if (cfil_info->cfi_flags & CFIF_DROP) {
#if DATA_DEBUG
		cfil_hash_entry_log(LOG_DEBUG, so, hash_entry, 0, "CFIL: UDP DROP");
#endif
		return (EPIPE);
	}
	if (control != NULL) {
		OSIncrementAtomic(&cfil_stats.cfs_data_in_control);
	}
	if (data->m_type == MT_OOBDATA) {
		CFIL_LOG(LOG_ERR, "so %llx MSG_OOB",
				 (uint64_t)VM_KERNEL_ADDRPERM(so));
		OSIncrementAtomic(&cfil_stats.cfs_data_in_oob);
	}

	error = cfil_data_common(so, cfil_info, outgoing, remote, data, control, flags);

	return (error);
}