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

/* Variables and functions */
 int EINVAL ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 int unp_connect2 (struct socket*,struct socket*) ; 

__attribute__((used)) static int
uipc_connect2(struct socket *so1, struct socket *so2)
{
	struct unpcb *unp = sotounpcb(so1);

	if (unp == 0)
		return (EINVAL);

	return (unp_connect2(so1, so2));
}