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
struct s3c2410_uartcfg {unsigned long ucon; unsigned long ulcon; unsigned long ufcon; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_UCON ; 
 int /*<<< orphan*/  S3C2410_UFCON ; 
 unsigned long S3C2410_UFCON_RESETBOTH ; 
 int /*<<< orphan*/  S3C2410_ULCON ; 
 unsigned long S3C6400_UCON_CLKMASK ; 
 int /*<<< orphan*/  dbg (char*,struct uart_port*,int /*<<< orphan*/ ,struct s3c2410_uartcfg*) ; 
 unsigned long rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr_regl (struct uart_port*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int s3c6400_serial_resetport(struct uart_port *port,
				    struct s3c2410_uartcfg *cfg)
{
	unsigned long ucon = rd_regl(port, S3C2410_UCON);

	dbg("s3c6400_serial_resetport: port=%p (%08lx), cfg=%p\n",
	    port, port->mapbase, cfg);

	/* ensure we don't change the clock settings... */

	ucon &= S3C6400_UCON_CLKMASK;

	wr_regl(port, S3C2410_UCON,  ucon | cfg->ucon);
	wr_regl(port, S3C2410_ULCON, cfg->ulcon);

	/* reset both fifos */

	wr_regl(port, S3C2410_UFCON, cfg->ufcon | S3C2410_UFCON_RESETBOTH);
	wr_regl(port, S3C2410_UFCON, cfg->ufcon);

	return 0;
}