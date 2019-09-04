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
struct unpcb {TYPE_1__* unp_conn; } ;
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {scalar_t__ unp_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 struct sockaddr* dup_sockaddr (struct sockaddr*,int) ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 int /*<<< orphan*/  sun_noname ; 

__attribute__((used)) static int
uipc_accept(struct socket *so, struct sockaddr **nam)
{
	struct unpcb *unp = sotounpcb(so);

	if (unp == 0)
		return (EINVAL);

	/*
	 * Pass back name of connected socket,
	 * if it was bound and we are still connected
	 * (our peer may have closed already!).
	 */
	if (unp->unp_conn && unp->unp_conn->unp_addr) {
		*nam = dup_sockaddr((struct sockaddr *)
		    unp->unp_conn->unp_addr, 1);
	} else {
		*nam = dup_sockaddr((struct sockaddr *)&sun_noname, 1);
	}
	return (0);
}