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
struct s3c24xx_uart_clksrc {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_UCON ; 
 unsigned long S3C2410_UCON_UCLK ; 
 unsigned long rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wr_regl (struct uart_port*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int s3c24a0_serial_setsource(struct uart_port *port,
				    struct s3c24xx_uart_clksrc *clk)
{
	unsigned long ucon = rd_regl(port, S3C2410_UCON);

	if (strcmp(clk->name, "uclk") == 0)
		ucon |= S3C2410_UCON_UCLK;
	else
		ucon &= ~S3C2410_UCON_UCLK;

	wr_regl(port, S3C2410_UCON, ucon);
	return 0;
}