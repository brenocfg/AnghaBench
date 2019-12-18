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
struct e100_serial {scalar_t__ uses_dma_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  e100_enable_rxdma_irq (struct e100_serial*) ; 
 int /*<<< orphan*/  e100_enable_serial_data_irq (struct e100_serial*) ; 

__attribute__((used)) static inline void e100_enable_rx_irq(struct e100_serial *info)
{
	if (info->uses_dma_in)
		e100_enable_rxdma_irq(info);
	else
		e100_enable_serial_data_irq(info);
}