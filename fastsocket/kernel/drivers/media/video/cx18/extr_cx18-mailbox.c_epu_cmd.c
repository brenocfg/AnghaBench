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
struct TYPE_2__ {int /*<<< orphan*/  cmd; } ;
struct cx18_in_work_order {int rpu; TYPE_1__ mb; } ;
struct cx18 {int dummy; } ;

/* Variables and functions */
#define  APU 131 
#define  CPU 130 
#define  CX18_EPU_DEBUG 129 
#define  CX18_EPU_DMA_DONE 128 
 int /*<<< orphan*/  CX18_WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epu_debug (struct cx18*,struct cx18_in_work_order*) ; 
 int /*<<< orphan*/  epu_dma_done (struct cx18*,struct cx18_in_work_order*) ; 

__attribute__((used)) static void epu_cmd(struct cx18 *cx, struct cx18_in_work_order *order)
{
	switch (order->rpu) {
	case CPU:
	{
		switch (order->mb.cmd) {
		case CX18_EPU_DMA_DONE:
			epu_dma_done(cx, order);
			break;
		case CX18_EPU_DEBUG:
			epu_debug(cx, order);
			break;
		default:
			CX18_WARN("Unknown CPU to EPU mailbox command %#0x\n",
				  order->mb.cmd);
			break;
		}
		break;
	}
	case APU:
		CX18_WARN("Unknown APU to EPU mailbox command %#0x\n",
			  order->mb.cmd);
		break;
	default:
		break;
	}
}