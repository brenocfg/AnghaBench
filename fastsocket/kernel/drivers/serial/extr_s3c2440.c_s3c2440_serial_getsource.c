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
 scalar_t__ S3C2410_UCON ; 
 unsigned long S3C2440_UCON0_DIVMASK ; 
 unsigned long S3C2440_UCON1_DIVMASK ; 
 unsigned long S3C2440_UCON2_DIVMASK ; 
 unsigned long S3C2440_UCON_CLKMASK ; 
 unsigned long S3C2440_UCON_DIVSHIFT ; 
#define  S3C2440_UCON_FCLK 131 
#define  S3C2440_UCON_PCLK 130 
#define  S3C2440_UCON_PCLK2 129 
#define  S3C2440_UCON_UCLK 128 
 scalar_t__ S3C24XX_VA_UART0 ; 
 scalar_t__ S3C24XX_VA_UART1 ; 
 scalar_t__ S3C24XX_VA_UART2 ; 
 unsigned long __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,unsigned long,unsigned long,unsigned long) ; 
 unsigned long rd_regl (struct uart_port*,scalar_t__) ; 

__attribute__((used)) static int s3c2440_serial_getsource(struct uart_port *port,
				    struct s3c24xx_uart_clksrc *clk)
{
	unsigned long ucon = rd_regl(port, S3C2410_UCON);
	unsigned long ucon0, ucon1, ucon2;

	switch (ucon & S3C2440_UCON_CLKMASK) {
	case S3C2440_UCON_UCLK:
		clk->divisor = 1;
		clk->name = "uclk";
		break;

	case S3C2440_UCON_PCLK:
	case S3C2440_UCON_PCLK2:
		clk->divisor = 1;
		clk->name = "pclk";
		break;

	case S3C2440_UCON_FCLK:
		/* the fun of calculating the uart divisors on
		 * the s3c2440 */

		ucon0 = __raw_readl(S3C24XX_VA_UART0 + S3C2410_UCON);
		ucon1 = __raw_readl(S3C24XX_VA_UART1 + S3C2410_UCON);
		ucon2 = __raw_readl(S3C24XX_VA_UART2 + S3C2410_UCON);

		printk("ucons: %08lx, %08lx, %08lx\n", ucon0, ucon1, ucon2);

		ucon0 &= S3C2440_UCON0_DIVMASK;
		ucon1 &= S3C2440_UCON1_DIVMASK;
		ucon2 &= S3C2440_UCON2_DIVMASK;

		if (ucon0 != 0) {
			clk->divisor = ucon0 >> S3C2440_UCON_DIVSHIFT;
			clk->divisor += 6;
		} else if (ucon1 != 0) {
			clk->divisor = ucon1 >> S3C2440_UCON_DIVSHIFT;
			clk->divisor += 21;
		} else if (ucon2 != 0) {
			clk->divisor = ucon2 >> S3C2440_UCON_DIVSHIFT;
			clk->divisor += 36;
		} else {
			/* manual calims 44, seems to be 9 */
			clk->divisor = 9;
		}

		clk->name = "fclk";
		break;
	}

	return 0;
}