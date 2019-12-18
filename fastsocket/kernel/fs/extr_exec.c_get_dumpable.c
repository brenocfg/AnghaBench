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
struct mm_struct {int flags; } ;

/* Variables and functions */

int get_dumpable(struct mm_struct *mm)
{
	int ret;

	ret = mm->flags & 0x3;
	return (ret >= 2) ? 2 : ret;
}