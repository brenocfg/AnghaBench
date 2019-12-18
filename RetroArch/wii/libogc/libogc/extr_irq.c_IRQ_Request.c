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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  raw_irq_handler_t ;
struct TYPE_2__ {void* pCtx; int /*<<< orphan*/  pHndl; } ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (size_t) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (size_t) ; 
 TYPE_1__* g_IRQHandler ; 

raw_irq_handler_t IRQ_Request(u32 nIrq,raw_irq_handler_t pHndl,void *pCtx)
{
	u32 level;

	_CPU_ISR_Disable(level);
	raw_irq_handler_t old = g_IRQHandler[nIrq].pHndl;
	g_IRQHandler[nIrq].pHndl = pHndl;
	g_IRQHandler[nIrq].pCtx = pCtx;
	_CPU_ISR_Restore(level);
	return old;
}