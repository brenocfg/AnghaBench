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
 unsigned char* port2adr (unsigned long) ; 
 scalar_t__ shifted_port (unsigned long) ; 

void se_outb(unsigned char value, unsigned long port)
{
	if (shifted_port(port))
		*(port2adr(port)) = value << 8;
	else
		*(port2adr(port)) = value;
}