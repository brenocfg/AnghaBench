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
struct socket {int so_flags; int so_flags1; int /*<<< orphan*/  so_zone; int /*<<< orphan*/  so_gencnt; int /*<<< orphan*/ * so_msg_state; int /*<<< orphan*/  so_cred; } ;
typedef  int /*<<< orphan*/  SInt64 ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE_ZONE (struct socket*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  OSIncrementAtomic64 (int /*<<< orphan*/ *) ; 
 int SOF1_CACHED_IN_SOCK_LAYER ; 
 int SOF_ENABLE_MSGS ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cached_sock_free (struct socket*) ; 
 int /*<<< orphan*/  cfil_sock_detach (struct socket*) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mac_socket_label_destroy (struct socket*) ; 
 int /*<<< orphan*/  sflt_termsock (struct socket*) ; 
 int /*<<< orphan*/  so_gencnt ; 

void
sodealloc(struct socket *so)
{
	kauth_cred_unref(&so->so_cred);

	/* Remove any filters */
	sflt_termsock(so);

#if CONTENT_FILTER
	cfil_sock_detach(so);
#endif /* CONTENT_FILTER */

	/* Delete the state allocated for msg queues on a socket */
	if (so->so_flags & SOF_ENABLE_MSGS) {
		FREE(so->so_msg_state, M_TEMP);
		so->so_msg_state = NULL;
	}
	VERIFY(so->so_msg_state == NULL);

	so->so_gencnt = OSIncrementAtomic64((SInt64 *)&so_gencnt);

#if CONFIG_MACF_SOCKET
	mac_socket_label_destroy(so);
#endif /* MAC_SOCKET */

	if (so->so_flags1 & SOF1_CACHED_IN_SOCK_LAYER) {
		cached_sock_free(so);
	} else {
		FREE_ZONE(so, sizeof (*so), so->so_zone);
	}
}