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
struct sbd_port {int dummy; } ;

/* Variables and functions */
 int M_DUART_CIN_CHNG_ENA ; 
 int M_DUART_CTS_CHNG_ENA ; 
 int /*<<< orphan*/  R_DUART_AUXCTL_X ; 
 struct sbd_port* to_sport (struct uart_port*) ; 
 int /*<<< orphan*/  write_sbdchn (struct sbd_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sbd_enable_ms(struct uart_port *uport)
{
	struct sbd_port *sport = to_sport(uport);

	write_sbdchn(sport, R_DUART_AUXCTL_X,
		     M_DUART_CIN_CHNG_ENA | M_DUART_CTS_CHNG_ENA);
}