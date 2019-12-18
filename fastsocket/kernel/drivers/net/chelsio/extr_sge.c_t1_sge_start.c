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
struct sge {scalar_t__ espibug_timeout; int /*<<< orphan*/  espibug_timer; TYPE_1__* adapter; int /*<<< orphan*/  tx_reclaim_timer; int /*<<< orphan*/  sge_control; int /*<<< orphan*/ * freelQ; } ;
struct TYPE_3__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ A_SG_CONTROL ; 
 int F_FL0_ENABLE ; 
 int F_FL1_ENABLE ; 
 scalar_t__ TX_RECLAIM_PERIOD ; 
 int /*<<< orphan*/  doorbell_pio (TYPE_1__*,int) ; 
 scalar_t__ is_T2 (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  refill_free_list (struct sge*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void t1_sge_start(struct sge *sge)
{
	refill_free_list(sge, &sge->freelQ[0]);
	refill_free_list(sge, &sge->freelQ[1]);

	writel(sge->sge_control, sge->adapter->regs + A_SG_CONTROL);
	doorbell_pio(sge->adapter, F_FL0_ENABLE | F_FL1_ENABLE);
	readl(sge->adapter->regs + A_SG_CONTROL); /* flush */

	mod_timer(&sge->tx_reclaim_timer, jiffies + TX_RECLAIM_PERIOD);

	if (is_T2(sge->adapter))
		mod_timer(&sge->espibug_timer, jiffies + sge->espibug_timeout);
}