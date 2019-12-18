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
typedef  int u32 ;
struct cx18 {int /*<<< orphan*/  mb_apu_waitq; int /*<<< orphan*/  mb_cpu_waitq; } ;

/* Variables and functions */
 int IRQ_APU_TO_EPU_ACK ; 
 int IRQ_CPU_TO_EPU_ACK ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xpu_ack(struct cx18 *cx, u32 sw2)
{
	if (sw2 & IRQ_CPU_TO_EPU_ACK)
		wake_up(&cx->mb_cpu_waitq);
	if (sw2 & IRQ_APU_TO_EPU_ACK)
		wake_up(&cx->mb_apu_waitq);
}