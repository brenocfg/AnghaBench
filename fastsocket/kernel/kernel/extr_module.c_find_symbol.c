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
struct module {int dummy; } ;
struct kernel_symbol {int dummy; } ;
struct find_symbol_arg {char const* name; int gplok; int warn; unsigned long* crc; struct kernel_symbol const* sym; struct module* owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGP (char*,char const*) ; 
 scalar_t__ each_symbol (int /*<<< orphan*/ ,struct find_symbol_arg*) ; 
 int /*<<< orphan*/  find_symbol_in_section ; 

const struct kernel_symbol *find_symbol(const char *name,
					struct module **owner,
					const unsigned long **crc,
					bool gplok,
					bool warn)
{
	struct find_symbol_arg fsa;

	fsa.name = name;
	fsa.gplok = gplok;
	fsa.warn = warn;

	if (each_symbol(find_symbol_in_section, &fsa)) {
		if (owner)
			*owner = fsa.owner;
		if (crc)
			*crc = fsa.crc;
		return fsa.sym;
	}

	DEBUGP("Failed to find symbol %s\n", name);
	return NULL;
}