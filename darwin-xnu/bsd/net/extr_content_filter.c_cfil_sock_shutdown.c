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
struct socket {int so_flags; int so_state; int /*<<< orphan*/  so_snd; TYPE_1__* so_cfil; } ;
struct TYPE_2__ {int cfi_flags; } ;

/* Variables and functions */
 int CFIF_DROP ; 
 int CFIF_SHUT_RD ; 
 int CFIF_SHUT_WR ; 
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int EJUSTRETURN ; 
 int ENOTCONN ; 
 scalar_t__ IS_UDP (struct socket*) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int SHUT_RD ; 
 int SHUT_RDWR ; 
 int SHUT_WR ; 
 int SOF_CONTENT_FILTER ; 
 int SS_CANTRCVMORE ; 
 int SS_CANTSENDMORE ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 scalar_t__ cfil_sock_data_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_sock_notify_shutdown (struct socket*,int) ; 
 int cfil_sock_udp_shutdown (struct socket*,int*) ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 

int
cfil_sock_shutdown(struct socket *so, int *how)
{
	int error = 0;

	if (IS_UDP(so)) {
		return (cfil_sock_udp_shutdown(so, how));
	}

	if ((so->so_flags & SOF_CONTENT_FILTER) == 0 || so->so_cfil == NULL)
		goto done;

	socket_lock_assert_owned(so);

	CFIL_LOG(LOG_INFO, "so %llx how %d",
		(uint64_t)VM_KERNEL_ADDRPERM(so), *how);

	/*
	 * Check the state of the socket before the content filter
	 */
	if (*how != SHUT_WR && (so->so_state & SS_CANTRCVMORE) != 0) {
		/* read already shut down */
		error = ENOTCONN;
		goto done;
	}
	if (*how != SHUT_RD && (so->so_state & SS_CANTSENDMORE) != 0) {
		/* write already shut down */
		error = ENOTCONN;
		goto done;
	}

	if ((so->so_cfil->cfi_flags & CFIF_DROP) != 0) {
		CFIL_LOG(LOG_ERR, "so %llx drop set",
			(uint64_t)VM_KERNEL_ADDRPERM(so));
		goto done;
	}

	/*
	 * shutdown read: SHUT_RD or SHUT_RDWR
	 */
	if (*how != SHUT_WR) {
		if (so->so_cfil->cfi_flags & CFIF_SHUT_RD) {
			error = ENOTCONN;
			goto done;
		}
		so->so_cfil->cfi_flags |= CFIF_SHUT_RD;
		cfil_sock_notify_shutdown(so, SHUT_RD);
	}
	/*
	 * shutdown write: SHUT_WR or SHUT_RDWR
	 */
	if (*how != SHUT_RD) {
		if (so->so_cfil->cfi_flags & CFIF_SHUT_WR) {
			error = ENOTCONN;
			goto done;
		}
		so->so_cfil->cfi_flags |= CFIF_SHUT_WR;
		cfil_sock_notify_shutdown(so, SHUT_WR);
		/*
		 * When outgoing data is pending, we delay the shutdown at the
		 * protocol level until the content filters give the final
		 * verdict on the pending data.
		 */
		if (cfil_sock_data_pending(&so->so_snd) != 0) {
			/*
			 * When shutting down the read and write sides at once
			 * we can proceed to the final shutdown of the read
			 * side. Otherwise, we just return.
			 */
			if (*how == SHUT_WR) {
				error = EJUSTRETURN;
			} else if (*how == SHUT_RDWR) {
				*how = SHUT_RD;
			}
		}
	}
done:
	return (error);
}