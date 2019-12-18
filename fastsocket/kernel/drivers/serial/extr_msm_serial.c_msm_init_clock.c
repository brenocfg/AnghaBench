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
struct uart_port {int dummy; } ;
struct msm_port {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_DREG ; 
 int /*<<< orphan*/  UART_MNDREG ; 
 int /*<<< orphan*/  UART_MREG ; 
 int /*<<< orphan*/  UART_NREG ; 
 struct msm_port* UART_TO_MSM (struct uart_port*) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_write (struct uart_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msm_init_clock(struct uart_port *port)
{
	struct msm_port *msm_port = UART_TO_MSM(port);

	clk_enable(msm_port->clk);

	msm_write(port, 0xC0, UART_MREG);
	msm_write(port, 0xB2, UART_NREG);
	msm_write(port, 0x7D, UART_DREG);
	msm_write(port, 0x1C, UART_MNDREG);
}