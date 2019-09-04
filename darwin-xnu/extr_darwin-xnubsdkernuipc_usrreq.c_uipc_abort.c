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
 int /*<<< orphan*/  ECONNABORTED ; 
 int EINVAL ; 
 int /*<<< orphan*/  sofree (struct socket*) ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 int /*<<< orphan*/  unp_detach (struct unpcb*) ; 
 int /*<<< orphan*/  unp_drop (struct unpcb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uipc_abort(struct socket *so)
{
	struct unpcb *unp = sotounpcb(so);

	if (unp == 0)
		return (EINVAL);
	unp_drop(unp, ECONNABORTED);
	unp_detach(unp);
	sofree(so);
	return (0);
}