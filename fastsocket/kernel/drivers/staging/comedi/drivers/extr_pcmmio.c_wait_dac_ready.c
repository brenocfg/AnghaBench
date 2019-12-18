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

__attribute__((used)) static int wait_dac_ready(unsigned long iobase)
{
	unsigned long retry = 100000L;

	/* This may seem like an absurd way to handle waiting and violates the
	   "no busy waiting" policy. The fact is that the hardware is
	   normally so fast that we usually only need one time through the loop
	   anyway. The longer timeout is for rare occasions and for detecting
	   non-existant hardware.  */

	while (retry--) {
		if (inb(iobase + 3) & 0x80)
			return 0;

	}
	return 1;
}