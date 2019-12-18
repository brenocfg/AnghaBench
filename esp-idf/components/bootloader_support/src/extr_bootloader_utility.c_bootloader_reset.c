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

/* Variables and functions */
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CNTL_OPTIONS0_REG ; 
 int /*<<< orphan*/  RTC_CNTL_SW_SYS_RST ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  ets_delay_us (int) ; 
 int /*<<< orphan*/  uart_tx_flush (int) ; 

void bootloader_reset(void)
{
#ifdef BOOTLOADER_BUILD
    uart_tx_flush(0);    /* Ensure any buffered log output is displayed */
    uart_tx_flush(1);
    ets_delay_us(1000); /* Allow last byte to leave FIFO */
    REG_WRITE(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_SW_SYS_RST);
    while (1) { }       /* This line will never be reached, used to keep gcc happy */
#else
    abort();            /* This function should really not be called from application code */
#endif
}