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
struct socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ cfil_filters_udp_attached (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfil_sock_udp_notify_shutdown (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 

void
cfil_sock_udp_close_wait(struct socket *so)
{
	socket_lock_assert_owned(so);

	while (cfil_filters_udp_attached(so, FALSE)) {
		/*
		 * Notify the filters we are going away so they can detach
		 */
		cfil_sock_udp_notify_shutdown(so, SHUT_RDWR, 0, 0);

		/*
		 * Make sure we need to wait after the filter are notified
		 * of the disconnection
		 */
		if (cfil_filters_udp_attached(so, TRUE) == 0)
			break;
	}
}