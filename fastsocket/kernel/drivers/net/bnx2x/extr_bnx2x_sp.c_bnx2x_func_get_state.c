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
struct bnx2x_func_sp_obj {int state; scalar_t__ pending; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_func_state { ____Placeholder_bnx2x_func_state } bnx2x_func_state ;

/* Variables and functions */
 int BNX2X_F_STATE_MAX ; 
 int /*<<< orphan*/  rmb () ; 

enum bnx2x_func_state bnx2x_func_get_state(struct bnx2x *bp,
					   struct bnx2x_func_sp_obj *o)
{
	/* in the middle of transaction - return INVALID state */
	if (o->pending)
		return BNX2X_F_STATE_MAX;

	/* unsure the order of reading of o->pending and o->state
	 * o->pending should be read first
	 */
	rmb();

	return o->state;
}