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
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ regs; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 scalar_t__ A_ESPI_CALENDAR_LENGTH ; 
 scalar_t__ A_ESPI_RX_FIFO_ALMOST_EMPTY_WATERMARK ; 
 scalar_t__ A_ESPI_RX_FIFO_ALMOST_FULL_WATERMARK ; 
 scalar_t__ A_ESPI_SCH_TOKEN0 ; 
 scalar_t__ A_ESPI_SCH_TOKEN1 ; 
 scalar_t__ A_ESPI_SCH_TOKEN2 ; 
 scalar_t__ A_ESPI_SCH_TOKEN3 ; 
 scalar_t__ A_ESPI_TRAIN ; 
 scalar_t__ A_PORT_CONFIG ; 
 int V_RX_NPORTS (int) ; 
 int V_TX_NPORTS (int) ; 
 scalar_t__ t1_is_T1B (TYPE_1__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void espi_setup_for_pm3393(adapter_t *adapter)
{
	u32 wmark = t1_is_T1B(adapter) ? 0x4000 : 0x3200;

	writel(0x1f4, adapter->regs + A_ESPI_SCH_TOKEN0);
	writel(0x1f4, adapter->regs + A_ESPI_SCH_TOKEN1);
	writel(0x1f4, adapter->regs + A_ESPI_SCH_TOKEN2);
	writel(0x1f4, adapter->regs + A_ESPI_SCH_TOKEN3);
	writel(0x100, adapter->regs + A_ESPI_RX_FIFO_ALMOST_EMPTY_WATERMARK);
	writel(wmark, adapter->regs + A_ESPI_RX_FIFO_ALMOST_FULL_WATERMARK);
	writel(3, adapter->regs + A_ESPI_CALENDAR_LENGTH);
	writel(0x08000008, adapter->regs + A_ESPI_TRAIN);
	writel(V_RX_NPORTS(1) | V_TX_NPORTS(1), adapter->regs + A_PORT_CONFIG);
}