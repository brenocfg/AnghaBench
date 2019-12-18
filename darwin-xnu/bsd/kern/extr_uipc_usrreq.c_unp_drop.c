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
struct unpcb {struct socket* unp_socket; } ;
struct socket {int so_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  unp_disconnect (struct unpcb*) ; 

__attribute__((used)) static void
unp_drop(struct unpcb *unp, int errno)
{
	struct socket *so = unp->unp_socket;

	so->so_error = errno;
	unp_disconnect(unp);
}