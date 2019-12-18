#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct adapter {TYPE_2__* slic_regs; TYPE_1__* card; } ;
struct TYPE_4__ {int /*<<< orphan*/  slic_reset; int /*<<< orphan*/  slic_quiesce; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ CARD_UP ; 
 int /*<<< orphan*/  FLUSH ; 
 int /*<<< orphan*/  SLIC_RESET_MAGIC ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  slic_reg32_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void slic_soft_reset(struct adapter *adapter)
{
	if (adapter->card->state == CARD_UP) {
		slic_reg32_write(&adapter->slic_regs->slic_quiesce, 0, FLUSH);
		mdelay(1);
	}

	slic_reg32_write(&adapter->slic_regs->slic_reset, SLIC_RESET_MAGIC,
			 FLUSH);
	mdelay(1);
}