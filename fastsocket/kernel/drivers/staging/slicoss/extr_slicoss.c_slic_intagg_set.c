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
typedef  int /*<<< orphan*/  u32 ;
struct adapter {TYPE_2__* card; TYPE_1__* slic_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  loadlevel_current; } ;
struct TYPE_3__ {int /*<<< orphan*/  slic_intagg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSH ; 
 int /*<<< orphan*/  slic_reg32_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void slic_intagg_set(struct adapter *adapter, u32 value)
{
	slic_reg32_write(&adapter->slic_regs->slic_intagg, value, FLUSH);
	adapter->card->loadlevel_current = value;
}