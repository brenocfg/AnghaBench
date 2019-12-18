#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sym_entry {TYPE_2__* sym; int /*<<< orphan*/ * name; } ;
struct TYPE_4__ {scalar_t__ st_value; } ;
struct TYPE_3__ {char* t_table; } ;

/* Variables and functions */
 scalar_t__ IS_UNDEF_SYM_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_sym_type (TYPE_2__*,char const*) ; 
 TYPE_1__* nm_print_data ; 
 int strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cmp_value(const void *lp, const void *rp)
{
	const struct sym_entry *l, *r;
	const char *ttable;
	int l_is_undef, r_is_undef;

	l = lp;
	r = rp;

	assert(nm_print_data != NULL);
	ttable = nm_print_data->t_table;

	assert(l != NULL);
	assert(l->name != NULL);
	assert(l->sym != NULL);
	assert(r != NULL);
	assert(r->name != NULL);
	assert(r->sym != NULL);
	assert(ttable != NULL);

	l_is_undef = IS_UNDEF_SYM_TYPE(get_sym_type(l->sym, ttable)) ? 1 : 0;
	r_is_undef = IS_UNDEF_SYM_TYPE(get_sym_type(r->sym, ttable)) ? 1 : 0;

	assert(l_is_undef + r_is_undef >= 0);
	assert(l_is_undef + r_is_undef <= 2);

	switch (l_is_undef + r_is_undef) {
	case 0:
		/* Both defined */
		if (l->sym->st_value == r->sym->st_value)
			return (strcmp(l->name, r->name));
		return (l->sym->st_value > r->sym->st_value ? 1 : -1);
	case 1:
		/* One undefined */
		return (l_is_undef == 0 ? 1 : -1);
	case 2:
		/* Both undefined */
		return (strcmp(l->name, r->name));
	}
	/* NOTREACHED */

	return (l->sym->st_value - r->sym->st_value);
}