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
typedef  size_t s32 ;
struct TYPE_2__ {int data_fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIIUSE_CONTINUOUS ; 
#define  WPAD_FMT_BTNS 130 
#define  WPAD_FMT_BTNS_ACC 129 
#define  WPAD_FMT_BTNS_ACC_IR 128 
 int /*<<< orphan*/ * __wpads ; 
 TYPE_1__* __wpdcb ; 
 int /*<<< orphan*/  wiiuse_motion_sensing (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wiiuse_set_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiiuse_set_ir (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __wpad_setfmt(s32 chan)
{
	switch(__wpdcb[chan].data_fmt) {
		case WPAD_FMT_BTNS:
			wiiuse_set_flags(__wpads[chan], 0, WIIUSE_CONTINUOUS);
			wiiuse_motion_sensing(__wpads[chan],0);
			wiiuse_set_ir(__wpads[chan],0);
			break;
		case WPAD_FMT_BTNS_ACC:
			wiiuse_set_flags(__wpads[chan], WIIUSE_CONTINUOUS, 0);
			wiiuse_motion_sensing(__wpads[chan],1);
			wiiuse_set_ir(__wpads[chan],0);
			break;
		case WPAD_FMT_BTNS_ACC_IR:
			wiiuse_set_flags(__wpads[chan], WIIUSE_CONTINUOUS, 0);
			wiiuse_motion_sensing(__wpads[chan],1);
			wiiuse_set_ir(__wpads[chan],1);
			break;
		default:
			break;
	}
}