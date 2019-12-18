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
struct s3c24xx_uart_info {int (* reset_port ) (struct uart_port*,struct s3c2410_uartcfg*) ;} ;
struct s3c2410_uartcfg {int dummy; } ;

/* Variables and functions */
 struct s3c24xx_uart_info* s3c24xx_port_to_info (struct uart_port*) ; 
 int stub1 (struct uart_port*,struct s3c2410_uartcfg*) ; 

__attribute__((used)) static inline int s3c24xx_serial_resetport(struct uart_port *port,
					   struct s3c2410_uartcfg *cfg)
{
	struct s3c24xx_uart_info *info = s3c24xx_port_to_info(port);

	return (info->reset_port)(port, cfg);
}