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
struct symbol {int flags; int /*<<< orphan*/  name; struct symbol* next; } ;

/* Variables and functions */
 int SYMBOL_CONST ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 struct symbol** symbol_hash ; 
 struct symbol symbol_mod ; 
 struct symbol symbol_no ; 
 struct symbol symbol_yes ; 

struct symbol *sym_find(const char *name)
{
	struct symbol *symbol = NULL;
	const char *ptr;
	int hash = 0;

	if (!name)
		return NULL;

	if (name[0] && !name[1]) {
		switch (name[0]) {
		case 'y': return &symbol_yes;
		case 'm': return &symbol_mod;
		case 'n': return &symbol_no;
		}
	}
	for (ptr = name; *ptr; ptr++)
		hash += *ptr;
	hash &= 0xff;

	for (symbol = symbol_hash[hash]; symbol; symbol = symbol->next) {
		if (!strcmp(symbol->name, name) &&
		    !(symbol->flags & SYMBOL_CONST))
				break;
	}

	return symbol;
}