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
typedef  int /*<<< orphan*/  u8 ;
struct xfrm_state_walk {scalar_t__ seq; int /*<<< orphan*/  state; int /*<<< orphan*/  proto; int /*<<< orphan*/  all; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XFRM_STATE_DEAD ; 

void xfrm_state_walk_init(struct xfrm_state_walk *walk, u8 proto)
{
	INIT_LIST_HEAD(&walk->all);
	walk->proto = proto;
	walk->state = XFRM_STATE_DEAD;
	walk->seq = 0;
}