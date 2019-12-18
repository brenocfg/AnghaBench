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
struct moxa_port {int lineCtrl; } ;

/* Variables and functions */
 int DTR_ON ; 
 int RTS_ON ; 

__attribute__((used)) static int MoxaPortGetLineOut(struct moxa_port *port, int *dtrState,
		int *rtsState)
{
	if (dtrState)
		*dtrState = !!(port->lineCtrl & DTR_ON);
	if (rtsState)
		*rtsState = !!(port->lineCtrl & RTS_ON);

	return 0;
}