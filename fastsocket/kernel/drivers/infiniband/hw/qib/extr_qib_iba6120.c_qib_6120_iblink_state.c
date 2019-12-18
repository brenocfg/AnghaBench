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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  IBCStatus ; 
#define  IB_6120_L_STATE_ACTIVE 132 
#define  IB_6120_L_STATE_ACT_DEFER 131 
#define  IB_6120_L_STATE_ARM 130 
#define  IB_6120_L_STATE_DOWN 129 
#define  IB_6120_L_STATE_INIT 128 
 int IB_PORT_ACTIVE ; 
 int IB_PORT_ARMED ; 
 int IB_PORT_DOWN ; 
 int IB_PORT_INIT ; 
 int /*<<< orphan*/  LinkState ; 
 int /*<<< orphan*/  SYM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 qib_6120_iblink_state(u64 ibcs)
{
	u32 state = (u32)SYM_FIELD(ibcs, IBCStatus, LinkState);

	switch (state) {
	case IB_6120_L_STATE_INIT:
		state = IB_PORT_INIT;
		break;
	case IB_6120_L_STATE_ARM:
		state = IB_PORT_ARMED;
		break;
	case IB_6120_L_STATE_ACTIVE:
		/* fall through */
	case IB_6120_L_STATE_ACT_DEFER:
		state = IB_PORT_ACTIVE;
		break;
	default: /* fall through */
	case IB_6120_L_STATE_DOWN:
		state = IB_PORT_DOWN;
		break;
	}
	return state;
}