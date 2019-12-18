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
 scalar_t__ PXSEG (unsigned long) ; 
 int /*<<< orphan*/  maybebadio (unsigned long) ; 
 unsigned short* port2adr (unsigned long) ; 

void snapgear_outw(unsigned short value, unsigned long port)
{
	if (PXSEG(port))
		*(volatile unsigned short *)port = value;
	else if (port >= 0x2000)
		*port2adr(port) = value;
	else
		maybebadio(port);
}