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
struct TYPE_2__ {scalar_t__ status; scalar_t__ hw_len; scalar_t__ sw_len; } ;
struct e100_serial {scalar_t__ line; int tr_running; scalar_t__ uses_dma_out; TYPE_1__ tr_descr; } ;

/* Variables and functions */
 scalar_t__ SERIAL_DEBUG_LINE ; 
 int /*<<< orphan*/  e100_enable_serial_tx_ready_irq (struct e100_serial*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  transmit_chars_dma (struct e100_serial*) ; 

__attribute__((used)) static void
start_transmit(struct e100_serial *info)
{
#if 0
	if (info->line == SERIAL_DEBUG_LINE)
		printk("x\n");
#endif

	info->tr_descr.sw_len = 0;
	info->tr_descr.hw_len = 0;
	info->tr_descr.status = 0;
	info->tr_running = 1;
	if (info->uses_dma_out)
		transmit_chars_dma(info);
	else
		e100_enable_serial_tx_ready_irq(info);
}