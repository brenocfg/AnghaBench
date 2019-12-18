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
struct symbol {struct property* prop; } ;
struct property {int type; struct property* next; int /*<<< orphan*/  lineno; int /*<<< orphan*/  file; struct symbol* sym; } ;
typedef  enum prop_type { ____Placeholder_prop_type } prop_type ;

/* Variables and functions */
 int /*<<< orphan*/  current_file ; 
 struct property* malloc (int) ; 
 int /*<<< orphan*/  memset (struct property*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zconf_lineno () ; 

struct property *prop_alloc(enum prop_type type, struct symbol *sym)
{
	struct property *prop;
	struct property **propp;

	prop = malloc(sizeof(*prop));
	memset(prop, 0, sizeof(*prop));
	prop->type = type;
	prop->sym = sym;
	prop->file = current_file;
	prop->lineno = zconf_lineno();

	/* append property to the prop list of symbol */
	if (sym) {
		for (propp = &sym->prop; *propp; propp = &(*propp)->next)
			;
		*propp = prop;
	}

	return prop;
}