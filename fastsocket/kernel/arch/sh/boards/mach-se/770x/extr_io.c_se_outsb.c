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
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int* port2adr (unsigned long) ; 
 scalar_t__ shifted_port (unsigned long) ; 

void se_outsb(unsigned long port, const void *addr, unsigned long count)
{
	volatile __u16 *p = port2adr(port);
	const __u8 *ap = addr;

	if (shifted_port(port)) {
		while (count--)
			*p = *ap++ << 8;
	} else {
		while (count--)
			*p = *ap++;
	}
}