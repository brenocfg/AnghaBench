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
struct unpcb {int /*<<< orphan*/ * unp_addr; } ;
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct sockaddr* dup_sockaddr (struct sockaddr*,int) ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 int /*<<< orphan*/  sun_noname ; 

__attribute__((used)) static int
uipc_sockaddr(struct socket *so, struct sockaddr **nam)
{
	struct unpcb *unp = sotounpcb(so);

	if (unp == NULL)
		return (EINVAL);
	if (unp->unp_addr != NULL) {
		*nam = dup_sockaddr((struct sockaddr *)unp->unp_addr, 1);
	} else {
		*nam = dup_sockaddr((struct sockaddr *)&sun_noname, 1);
	}
	return (0);
}