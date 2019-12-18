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
 int /*<<< orphan*/  ctrl_delay () ; 
 int* port2adr (unsigned long) ; 

unsigned char snapgear_inb_p(unsigned long port)
{
	unsigned char v;

	if (PXSEG(port))
		v = *(volatile unsigned char *)port;
	else
		v = (*port2adr(port))&0xff;
	ctrl_delay();
	return v;
}