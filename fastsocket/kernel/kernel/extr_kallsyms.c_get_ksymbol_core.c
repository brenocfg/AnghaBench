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
struct kallsym_iter {unsigned int nameoff; char* module_name; size_t pos; int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/ * kallsyms_addresses ; 
 unsigned int kallsyms_expand_symbol (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kallsyms_get_symbol_type (unsigned int) ; 

__attribute__((used)) static unsigned long get_ksymbol_core(struct kallsym_iter *iter)
{
	unsigned off = iter->nameoff;

	iter->module_name[0] = '\0';
	iter->value = kallsyms_addresses[iter->pos];

	iter->type = kallsyms_get_symbol_type(off);

	off = kallsyms_expand_symbol(off, iter->name);

	return off - iter->nameoff;
}