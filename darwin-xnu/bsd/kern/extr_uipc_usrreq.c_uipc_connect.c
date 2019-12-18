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
struct unpcb {int dummy; } ;
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int EINVAL ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 int unp_connect (struct socket*,struct sockaddr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uipc_connect(struct socket *so, struct sockaddr *nam, proc_t p)
{
	struct unpcb *unp = sotounpcb(so);

	if (unp == 0)
		return (EINVAL);
	return (unp_connect(so, nam, p));
}