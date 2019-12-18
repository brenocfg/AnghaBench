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
 unsigned long S3C2412_UCON_CLKMASK ; 
#define  S3C2412_UCON_PCLK 131 
#define  S3C2412_UCON_PCLK2 130 
#define  S3C2412_UCON_UCLK 129 
#define  S3C2412_UCON_USYSCLK 128 
 unsigned long rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c2412_serial_getsource(struct uart_port *port,
				    struct s3c24xx_uart_clksrc *clk)
{
	unsigned long ucon = rd_regl(port, S3C2410_UCON);

	switch (ucon & S3C2412_UCON_CLKMASK) {
	case S3C2412_UCON_UCLK:
		clk->divisor = 1;
		clk->name = "uclk";
		break;

	case S3C2412_UCON_PCLK:
	case S3C2412_UCON_PCLK2:
		clk->divisor = 1;
		clk->name = "pclk";
		break;

	case S3C2412_UCON_USYSCLK:
		clk->divisor = 1;
		clk->name = "usysclk";
		break;
	}

	return 0;
}