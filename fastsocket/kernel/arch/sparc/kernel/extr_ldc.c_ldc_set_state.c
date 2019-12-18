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
struct ldc_channel {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE ; 
 int /*<<< orphan*/  ldcdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ldc_set_state(struct ldc_channel *lp, u8 state)
{
	ldcdbg(STATE, "STATE (%s) --> (%s)\n",
	       state_to_str(lp->state),
	       state_to_str(state));

	lp->state = state;
}