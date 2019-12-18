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
struct kallsym_iter {scalar_t__ pos; int /*<<< orphan*/  nameoff; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ get_ksymbol_core (struct kallsym_iter*) ; 
 int get_ksymbol_mod (struct kallsym_iter*) ; 
 scalar_t__ kallsyms_num_syms ; 
 int /*<<< orphan*/  reset_iter (struct kallsym_iter*,scalar_t__) ; 

__attribute__((used)) static int update_iter(struct kallsym_iter *iter, loff_t pos)
{
	/* Module symbols can be accessed randomly. */
	if (pos >= kallsyms_num_syms) {
		iter->pos = pos;
		return get_ksymbol_mod(iter);
	}

	/* If we're not on the desired position, reset to new position. */
	if (pos != iter->pos)
		reset_iter(iter, pos);

	iter->nameoff += get_ksymbol_core(iter);
	iter->pos++;

	return 1;
}