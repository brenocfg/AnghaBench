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
 unsigned long readl (unsigned long) ; 

void insl(unsigned long addr, void *dst, unsigned long count) {
        while (count) {
                count -= 4;
                /*
                 * XXX I am sure we are in for an unaligned trap here.
                 */
                *(unsigned long *)dst = readl(addr);
                dst += 4;
                addr += 4;
        }
}