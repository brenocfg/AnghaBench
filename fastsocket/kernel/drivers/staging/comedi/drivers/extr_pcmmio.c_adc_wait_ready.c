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
 int inb (unsigned long) ; 

__attribute__((used)) static int adc_wait_ready(unsigned long iobase)
{
	unsigned long retry = 100000;
	while (retry--)
		if (inb(iobase + 3) & 0x80)
			return 0;
	return 1;
}