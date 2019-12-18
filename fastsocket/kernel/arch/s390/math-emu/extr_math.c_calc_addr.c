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
struct pt_regs {int* gprs; } ;
typedef  int addr_t ;

/* Variables and functions */

__attribute__((used)) static void* calc_addr(struct pt_regs *regs, int rx, int rb, int disp)
{
        addr_t addr;

        rx &= 15;
        rb &= 15;
        addr = disp & 0xfff;
        addr += (rx != 0) ? regs->gprs[rx] : 0;  /* + index */
        addr += (rb != 0) ? regs->gprs[rb] : 0;  /* + base  */
        return (void*) addr;
}