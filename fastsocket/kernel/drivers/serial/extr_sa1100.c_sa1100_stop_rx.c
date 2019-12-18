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
typedef  int u32 ;
struct uart_port {int dummy; } ;
struct sa1100_port {int dummy; } ;

/* Variables and functions */
 int UART_GET_UTCR3 (struct sa1100_port*) ; 
 int /*<<< orphan*/  UART_PUT_UTCR3 (struct sa1100_port*,int) ; 
 int UTCR3_RIE ; 

__attribute__((used)) static void sa1100_stop_rx(struct uart_port *port)
{
	struct sa1100_port *sport = (struct sa1100_port *)port;
	u32 utcr3;

	utcr3 = UART_GET_UTCR3(sport);
	UART_PUT_UTCR3(sport, utcr3 & ~UTCR3_RIE);
}