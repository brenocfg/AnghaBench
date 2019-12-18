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

/* Variables and functions */
 unsigned char PARPORT_CONTROL_AUTOFD ; 
 unsigned char PARPORT_CONTROL_SELECT ; 
 unsigned char PARPORT_CONTROL_STROBE ; 

__attribute__((used)) static unsigned char control_amiga_to_pc(unsigned char control)
{
	return PARPORT_CONTROL_SELECT |
	      PARPORT_CONTROL_AUTOFD | PARPORT_CONTROL_STROBE;
	/* fake value: interrupt enable, select in, no reset,
	no autolf, no strobe - seems to be closest the wiring diagram */
}