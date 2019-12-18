#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;
struct uart_txx9_port {TYPE_1__ port; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TXX9_SIDICR ; 
 int /*<<< orphan*/  TXX9_SIFCR ; 
 int TXX9_SIFCR_RDIL_1 ; 
 int TXX9_SIFCR_SWRST ; 
 int TXX9_SIFCR_TDIL_MAX ; 
 int /*<<< orphan*/  TXX9_SIFLCR ; 
 int TXX9_SIFLCR_RTSTL_MAX ; 
 int /*<<< orphan*/  TXX9_SILCR ; 
 int TXX9_SILCR_SCS_IMCLK_BG ; 
 int TXX9_SILCR_SCS_SCLK_BG ; 
 int TXX9_SILCR_UMODE_8BIT ; 
 int TXX9_SILCR_USBL_1BIT ; 
 int UPF_TXX9_USE_SCLK ; 
 int /*<<< orphan*/  mmiowb () ; 
 int sio_in (struct uart_txx9_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_out (struct uart_txx9_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sio_quot_set (struct uart_txx9_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_set (struct uart_txx9_port*,int /*<<< orphan*/ ,int) ; 
 struct uart_txx9_port* to_uart_txx9_port (struct uart_port*) ; 
 int /*<<< orphan*/  uart_get_divisor (struct uart_port*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void serial_txx9_initialize(struct uart_port *port)
{
	struct uart_txx9_port *up = to_uart_txx9_port(port);
	unsigned int tmout = 10000;

	sio_out(up, TXX9_SIFCR, TXX9_SIFCR_SWRST);
	/* TX4925 BUG WORKAROUND.  Accessing SIOC register
	 * immediately after soft reset causes bus error. */
	mmiowb();
	udelay(1);
	while ((sio_in(up, TXX9_SIFCR) & TXX9_SIFCR_SWRST) && --tmout)
		udelay(1);
	/* TX Int by FIFO Empty, RX Int by Receiving 1 char. */
	sio_set(up, TXX9_SIFCR,
		TXX9_SIFCR_TDIL_MAX | TXX9_SIFCR_RDIL_1);
	/* initial settings */
	sio_out(up, TXX9_SILCR,
		TXX9_SILCR_UMODE_8BIT | TXX9_SILCR_USBL_1BIT |
		((up->port.flags & UPF_TXX9_USE_SCLK) ?
		 TXX9_SILCR_SCS_SCLK_BG : TXX9_SILCR_SCS_IMCLK_BG));
	sio_quot_set(up, uart_get_divisor(port, 9600));
	sio_out(up, TXX9_SIFLCR, TXX9_SIFLCR_RTSTL_MAX /* 15 */);
	sio_out(up, TXX9_SIDICR, 0);
}