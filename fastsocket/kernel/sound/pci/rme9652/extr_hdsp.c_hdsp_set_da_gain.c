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
struct hdsp {int /*<<< orphan*/  control_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSP_DAGainHighGain ; 
 int /*<<< orphan*/  HDSP_DAGainMask ; 
 int /*<<< orphan*/  HDSP_DAGainMinus10dBV ; 
 int /*<<< orphan*/  HDSP_DAGainPlus4dBu ; 
 int /*<<< orphan*/  HDSP_controlRegister ; 
 int /*<<< orphan*/  hdsp_write (struct hdsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdsp_set_da_gain(struct hdsp *hdsp, int mode)
{
	hdsp->control_register &= ~HDSP_DAGainMask;
	switch (mode) {
	case 0:
		hdsp->control_register |= HDSP_DAGainHighGain;
		break;
	case 1:
		hdsp->control_register |= HDSP_DAGainPlus4dBu;
		break;
	case 2:
		hdsp->control_register |= HDSP_DAGainMinus10dBV;
		break;
	default:
		return -1;

	}
	hdsp_write(hdsp, HDSP_controlRegister, hdsp->control_register);
	return 0;
}