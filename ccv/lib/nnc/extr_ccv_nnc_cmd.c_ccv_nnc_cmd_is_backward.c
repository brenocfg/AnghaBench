#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cmd; } ;
typedef  TYPE_1__ ccv_nnc_cmd_t ;

/* Variables and functions */
#define  CCV_NNC_CUSTOM_BACKWARD 132 
#define  CCV_NNC_CUSTOM_FORWARD 131 
#define  CCV_NNC_GRAPH_BACKWARD 130 
#define  CCV_NNC_GRAPH_FORWARD 129 
#define  CCV_NNC_NOOP 128 

int ccv_nnc_cmd_is_backward(const ccv_nnc_cmd_t cmd)
{
	switch (cmd.cmd)
	{
		case CCV_NNC_NOOP:
			return 0;
		case CCV_NNC_CUSTOM_FORWARD:
		case CCV_NNC_CUSTOM_BACKWARD:
		case CCV_NNC_GRAPH_FORWARD:
		case CCV_NNC_GRAPH_BACKWARD:
		default:
			return !!(cmd.cmd & 0x1); // If it is odd, it is backward
	}
}