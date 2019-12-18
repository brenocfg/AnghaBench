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
struct uart_port {int dummy; } ;
struct TYPE_2__ {scalar_t__ membase; } ;
struct imx_port {TYPE_1__ port; } ;

/* Variables and functions */
 unsigned int TIOCSER_TEMT ; 
 scalar_t__ USR2 ; 
 int USR2_TXDC ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static unsigned int imx_tx_empty(struct uart_port *port)
{
	struct imx_port *sport = (struct imx_port *)port;

	return (readl(sport->port.membase + USR2) & USR2_TXDC) ?  TIOCSER_TEMT : 0;
}