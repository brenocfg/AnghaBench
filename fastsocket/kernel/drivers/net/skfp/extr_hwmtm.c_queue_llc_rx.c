#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  isr_flag; TYPE_3__* llc_rx_tail; TYPE_3__* llc_rx_pipe; int /*<<< orphan*/  queued_rx_frames; } ;
struct TYPE_5__ {TYPE_2__ hwm; } ;
struct s_smc {TYPE_1__ os; } ;
struct TYPE_7__ {struct TYPE_7__* sm_next; } ;
typedef  TYPE_3__ SMbuf ;

/* Variables and functions */
 int /*<<< orphan*/  DB_GEN (char*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smt_force_irq (struct s_smc*) ; 

__attribute__((used)) static void queue_llc_rx(struct s_smc *smc, SMbuf *mb)
{
	DB_GEN("queue_llc_rx: mb = %x",(void *)mb,0,4) ;
	smc->os.hwm.queued_rx_frames++ ;
	mb->sm_next = (SMbuf *)NULL ;
	if (smc->os.hwm.llc_rx_pipe == NULL) {
		smc->os.hwm.llc_rx_pipe = mb ;
	}
	else {
		smc->os.hwm.llc_rx_tail->sm_next = mb ;
	}
	smc->os.hwm.llc_rx_tail = mb ;

	/*
	 * force an timer IRQ to receive the data
	 */
	if (!smc->os.hwm.isr_flag) {
		smt_force_irq(smc) ;
	}
}