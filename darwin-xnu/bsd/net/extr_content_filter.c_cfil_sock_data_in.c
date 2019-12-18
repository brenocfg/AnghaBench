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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct socket {int so_flags; TYPE_2__* so_cfil; } ;
struct sockaddr {int dummy; } ;
struct mbuf {scalar_t__ m_type; } ;
struct TYPE_4__ {int cfi_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  cfs_data_in_oob; int /*<<< orphan*/  cfs_data_in_control; } ;

/* Variables and functions */
 int CFIF_DROP ; 
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int EPIPE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IS_UDP (struct socket*) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ MT_OOBDATA ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 int SOF_CONTENT_FILTER ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 int cfil_data_common (struct socket*,TYPE_2__*,int /*<<< orphan*/ ,struct sockaddr*,struct mbuf*,struct mbuf*,int /*<<< orphan*/ ) ; 
 int cfil_sock_udp_handle_data (int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ *,struct sockaddr*,struct mbuf*,struct mbuf*,int /*<<< orphan*/ ) ; 
 TYPE_1__ cfil_stats ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 

int
cfil_sock_data_in(struct socket *so, struct sockaddr *from,
	struct mbuf *data, struct mbuf *control, uint32_t flags)
{
	int error = 0;

	if (IS_UDP(so)) {
        return (cfil_sock_udp_handle_data(FALSE, so, NULL, from, data, control, flags));
    }

	if ((so->so_flags & SOF_CONTENT_FILTER) == 0 || so->so_cfil == NULL)
		return (0);

	socket_lock_assert_owned(so);

	if (so->so_cfil->cfi_flags & CFIF_DROP) {
		CFIL_LOG(LOG_ERR, "so %llx drop set",
			(uint64_t)VM_KERNEL_ADDRPERM(so));
		return (EPIPE);
	}
	if (control != NULL) {
		CFIL_LOG(LOG_ERR, "so %llx control",
			(uint64_t)VM_KERNEL_ADDRPERM(so));
		OSIncrementAtomic(&cfil_stats.cfs_data_in_control);
	}
	if (data->m_type == MT_OOBDATA) {
		CFIL_LOG(LOG_ERR, "so %llx MSG_OOB",
			(uint64_t)VM_KERNEL_ADDRPERM(so));
		OSIncrementAtomic(&cfil_stats.cfs_data_in_oob);
	}
	error = cfil_data_common(so, so->so_cfil, 0, from, data, control, flags);

	return (error);
}