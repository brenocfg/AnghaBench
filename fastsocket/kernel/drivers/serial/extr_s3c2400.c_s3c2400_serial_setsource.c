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
struct s3c24xx_uart_clksrc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int s3c2400_serial_setsource(struct uart_port *port,
				    struct s3c24xx_uart_clksrc *clk)
{
	return 0;
}