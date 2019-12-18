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
 int /*<<< orphan*/  outb (unsigned char const,unsigned long) ; 

void outsb(unsigned long port, const void * src, unsigned long count)
{
	const unsigned char *p;

	p = (const unsigned char *)src;
	while (count) {
		count--;
		outb(*p, port);
		p++;
	}
}