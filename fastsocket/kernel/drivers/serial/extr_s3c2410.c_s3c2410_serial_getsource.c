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
struct s3c24xx_uart_clksrc {int divisor; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_UCON ; 
 unsigned long S3C2410_UCON_UCLK ; 
 unsigned long rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c2410_serial_getsource(struct uart_port *port,
				    struct s3c24xx_uart_clksrc *clk)
{
	unsigned long ucon = rd_regl(port, S3C2410_UCON);

	clk->divisor = 1;
	clk->name = (ucon & S3C2410_UCON_UCLK) ? "uclk" : "pclk";

	return 0;
}