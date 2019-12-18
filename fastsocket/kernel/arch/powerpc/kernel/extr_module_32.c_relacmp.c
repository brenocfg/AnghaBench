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
struct TYPE_2__ {scalar_t__ r_info; scalar_t__ r_addend; } ;
typedef  TYPE_1__ Elf32_Rela ;

/* Variables and functions */

__attribute__((used)) static int relacmp(const void *_x, const void *_y)
{
	const Elf32_Rela *x, *y;

	y = (Elf32_Rela *)_x;
	x = (Elf32_Rela *)_y;

	/* Compare the entire r_info (as opposed to ELF32_R_SYM(r_info) only) to
	 * make the comparison cheaper/faster. It won't affect the sorting or
	 * the counting algorithms' performance
	 */
	if (x->r_info < y->r_info)
		return -1;
	else if (x->r_info > y->r_info)
		return 1;
	else if (x->r_addend < y->r_addend)
		return -1;
	else if (x->r_addend > y->r_addend)
		return 1;
	else
		return 0;
}