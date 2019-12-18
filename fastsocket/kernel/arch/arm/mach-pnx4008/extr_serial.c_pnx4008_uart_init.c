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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SE_U3_RX_INT ; 
 int /*<<< orphan*/  SE_U5_RX_INT ; 
 scalar_t__ UART3_BASE_VA ; 
 scalar_t__ UART5_BASE_VA ; 
 scalar_t__ UART_FCR_OFFSET ; 
 int UART_FIFO_SIZE ; 
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  start_int_ack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_int_set_rising_edge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_int_umask (int /*<<< orphan*/ ) ; 

void pnx4008_uart_init(void)
{
	u32 tmp;
	int i = UART_FIFO_SIZE;

	__raw_writel(0xC1, UART5_BASE_VA + UART_FCR_OFFSET);
	__raw_writel(0xC1, UART3_BASE_VA + UART_FCR_OFFSET);

	/* Send a NULL to fix the UART HW bug */
	__raw_writel(0x00, UART5_BASE_VA);
	__raw_writel(0x00, UART3_BASE_VA);

	while (i--) {
		tmp = __raw_readl(UART5_BASE_VA);
		tmp = __raw_readl(UART3_BASE_VA);
	}
	__raw_writel(0, UART5_BASE_VA + UART_FCR_OFFSET);
	__raw_writel(0, UART3_BASE_VA + UART_FCR_OFFSET);

	/* setup wakeup interrupt */
	start_int_set_rising_edge(SE_U3_RX_INT);
	start_int_ack(SE_U3_RX_INT);
	start_int_umask(SE_U3_RX_INT);

	start_int_set_rising_edge(SE_U5_RX_INT);
	start_int_ack(SE_U5_RX_INT);
	start_int_umask(SE_U5_RX_INT);
}