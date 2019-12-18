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
 unsigned int* port2adr (unsigned long) ; 

unsigned int sh7751se_inl(unsigned long port)
{
        if (PXSEG(port))
                return *(volatile unsigned long *)port;
	else if (port >= 0x2000)
		return *port2adr(port);
	else
		maybebadio(port);
	return 0;
}