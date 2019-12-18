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
 int /*<<< orphan*/  memcpy (unsigned long*,unsigned char const*,int) ; 
 int /*<<< orphan*/  outl (unsigned long,unsigned long) ; 

void __outsl(unsigned long addr, const void *buffer, int count)
{
	const unsigned char *buf = buffer;
	unsigned long val;

	while (count--) {
		memcpy(&val, buf, 4);
		outl(val, addr);
		buf += 4;
	}
}