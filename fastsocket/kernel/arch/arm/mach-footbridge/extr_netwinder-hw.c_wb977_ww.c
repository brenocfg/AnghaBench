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
 int /*<<< orphan*/  outb (int,int) ; 

__attribute__((used)) static inline void wb977_ww(int reg, int val)
{
	outb(reg, 0x370);
	outb(val >> 8, 0x371);
	outb(reg + 1, 0x370);
	outb(val & 255, 0x371);
}