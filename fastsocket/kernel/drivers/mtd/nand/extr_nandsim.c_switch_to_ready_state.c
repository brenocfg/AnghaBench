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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int /*<<< orphan*/  status; scalar_t__ column; scalar_t__ row; scalar_t__ off; scalar_t__ count; scalar_t__ num; } ;
struct nandsim {TYPE_1__ regs; scalar_t__ stateidx; scalar_t__ npstates; int /*<<< orphan*/ * op; int /*<<< orphan*/  nxstate; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NS_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_READY ; 
 int /*<<< orphan*/  STATE_UNKNOWN ; 
 int /*<<< orphan*/  get_state_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void switch_to_ready_state(struct nandsim *ns, u_char status)
{
	NS_DBG("switch_to_ready_state: switch to %s state\n", get_state_name(STATE_READY));

	ns->state       = STATE_READY;
	ns->nxstate     = STATE_UNKNOWN;
	ns->op          = NULL;
	ns->npstates    = 0;
	ns->stateidx    = 0;
	ns->regs.num    = 0;
	ns->regs.count  = 0;
	ns->regs.off    = 0;
	ns->regs.row    = 0;
	ns->regs.column = 0;
	ns->regs.status = status;
}