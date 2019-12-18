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
struct kallsym_iter {int /*<<< orphan*/  exported; int /*<<< orphan*/  module_name; int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  value; scalar_t__ pos; } ;

/* Variables and functions */
 scalar_t__ kallsyms_num_syms ; 
 scalar_t__ module_get_kallsym (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_ksymbol_mod(struct kallsym_iter *iter)
{
	if (module_get_kallsym(iter->pos - kallsyms_num_syms, &iter->value,
				&iter->type, iter->name, iter->module_name,
				&iter->exported) < 0)
		return 0;
	return 1;
}