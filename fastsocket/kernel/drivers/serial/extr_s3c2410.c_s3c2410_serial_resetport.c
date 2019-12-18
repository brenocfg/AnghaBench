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
struct uart_port {int /*<<< orphan*/  mapbase; } ;
struct s3c2410_uartcfg {int ucon; int ulcon; int ufcon; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_UCON ; 
 int /*<<< orphan*/  S3C2410_UFCON ; 
 int S3C2410_UFCON_RESETBOTH ; 
 int /*<<< orphan*/  S3C2410_ULCON ; 
 int /*<<< orphan*/  dbg (char*,struct uart_port*,int /*<<< orphan*/ ,struct s3c2410_uartcfg*) ; 
 int /*<<< orphan*/  wr_regl (struct uart_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int s3c2410_serial_resetport(struct uart_port *port,
				    struct s3c2410_uartcfg *cfg)
{
	dbg("s3c2410_serial_resetport: port=%p (%08lx), cfg=%p\n",
	    port, port->mapbase, cfg);

	wr_regl(port, S3C2410_UCON,  cfg->ucon);
	wr_regl(port, S3C2410_ULCON, cfg->ulcon);

	/* reset both fifos */

	wr_regl(port, S3C2410_UFCON, cfg->ufcon | S3C2410_UFCON_RESETBOTH);
	wr_regl(port, S3C2410_UFCON, cfg->ufcon);

	return 0;
}