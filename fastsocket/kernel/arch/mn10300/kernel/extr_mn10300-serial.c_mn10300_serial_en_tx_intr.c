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
typedef  int u16 ;
struct mn10300_serial_port {int* tx_icr; } ;

/* Variables and functions */
 int GxICR_ENABLE ; 
 int GxICR_LEVEL_1 ; 

__attribute__((used)) static void mn10300_serial_en_tx_intr(struct mn10300_serial_port *port)
{
	u16 x;
	*port->tx_icr = GxICR_LEVEL_1 | GxICR_ENABLE;
	x = *port->tx_icr;
}