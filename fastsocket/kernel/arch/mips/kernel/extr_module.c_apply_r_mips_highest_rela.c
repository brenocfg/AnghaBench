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
typedef  int u32 ;
struct module {int dummy; } ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */

__attribute__((used)) static int apply_r_mips_highest_rela(struct module *me, u32 *location,
				     Elf_Addr v)
{
	*location = (*location & 0xffff0000) |
	            ((((long long) v + 0x800080008000LL) >> 48) & 0xffff);

	return 0;
}