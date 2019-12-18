#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long mask; } ;
struct pt_regs {TYPE_1__ psw; } ;

/* Variables and functions */

__attribute__((used)) static inline int mask_bits(struct pt_regs *regs, unsigned long bits)
{
	return (regs->psw.mask & bits) / ((~bits + 1) & bits);
}