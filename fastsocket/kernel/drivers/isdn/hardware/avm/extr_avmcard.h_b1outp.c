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
 scalar_t__ B1_ANALYSE ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,unsigned int) ; 

__attribute__((used)) static inline unsigned char b1outp(unsigned int base,
				   unsigned short offset,
				   unsigned char value)
{
	outb(value, base + offset);
	return inb(base + B1_ANALYSE);
}