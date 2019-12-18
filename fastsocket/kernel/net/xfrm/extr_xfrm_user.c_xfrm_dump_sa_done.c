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
struct xfrm_state_walk {int dummy; } ;
struct netlink_callback {int /*<<< orphan*/ * args; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfrm_state_walk_done (struct xfrm_state_walk*) ; 

__attribute__((used)) static int xfrm_dump_sa_done(struct netlink_callback *cb)
{
	struct xfrm_state_walk *walk = (struct xfrm_state_walk *) &cb->args[1];
	xfrm_state_walk_done(walk);
	return 0;
}