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
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 unsigned long PAGE_ALIGN (scalar_t__) ; 
 int PF_RANDOMIZE ; 
 scalar_t__ brk_rnd () ; 
 TYPE_1__* current ; 

unsigned long randomize_et_dyn(unsigned long base)
{
	unsigned long ret = PAGE_ALIGN(base + brk_rnd());

	if (!(current->flags & PF_RANDOMIZE))
		return base;
	if (ret < base)
		return base;
	return ret;
}