#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct peespi {int misc_ctrl; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {scalar_t__ regs; struct peespi* espi; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 scalar_t__ A_ESPI_MISC_CONTROL ; 
 scalar_t__ A_ESPI_SCH_TOKEN3 ; 
 int MON_MASK ; 
 int V_MONITORED_PORT_NUM (int) ; 
 int /*<<< orphan*/  is_T2 (TYPE_1__*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

u32 t1_espi_get_mon(adapter_t *adapter, u32 addr, u8 wait)
{
	struct peespi *espi = adapter->espi;
	u32 sel;

	if (!is_T2(adapter))
		return 0;

	sel = V_MONITORED_PORT_NUM((addr & 0x3c) >> 2);
	if (!wait) {
		if (!spin_trylock(&espi->lock))
			return 0;
	} else
		spin_lock(&espi->lock);

	if ((sel != (espi->misc_ctrl & MON_MASK))) {
		writel(((espi->misc_ctrl & ~MON_MASK) | sel),
		       adapter->regs + A_ESPI_MISC_CONTROL);
		sel = readl(adapter->regs + A_ESPI_SCH_TOKEN3);
		writel(espi->misc_ctrl, adapter->regs + A_ESPI_MISC_CONTROL);
	} else
		sel = readl(adapter->regs + A_ESPI_SCH_TOKEN3);
	spin_unlock(&espi->lock);
	return sel;
}