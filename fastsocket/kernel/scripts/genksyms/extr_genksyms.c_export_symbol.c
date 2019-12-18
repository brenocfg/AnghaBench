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
struct symbol {scalar_t__ status; struct symbol* expansion_trail; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ STATUS_DEFINED ; 
 scalar_t__ STATUS_UNCHANGED ; 
 int /*<<< orphan*/  SYM_NORMAL ; 
 int /*<<< orphan*/  debugfile ; 
 int /*<<< orphan*/  error_with_pos (char*,char const*) ; 
 int /*<<< orphan*/  errors ; 
 int expand_and_crc_sym (struct symbol*,int) ; 
 struct symbol* expansion_trail ; 
 struct symbol* find_symbol (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_dump_defs ; 
 scalar_t__ flag_preserve ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 char* mod_prefix ; 
 int /*<<< orphan*/  print_location () ; 
 int /*<<< orphan*/  print_type_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char const*,unsigned long) ; 
 int /*<<< orphan*/  stderr ; 

void export_symbol(const char *name)
{
	struct symbol *sym;

	sym = find_symbol(name, SYM_NORMAL);
	if (!sym)
		error_with_pos("export undefined symbol %s", name);
	else {
		unsigned long crc;
		int has_changed = 0;

		if (flag_dump_defs)
			fprintf(debugfile, "Export %s == <", name);

		expansion_trail = (struct symbol *)-1L;

		sym->expansion_trail = expansion_trail;
		expansion_trail = sym;
		crc = expand_and_crc_sym(sym, 0xffffffff) ^ 0xffffffff;

		sym = expansion_trail;
		while (sym != (struct symbol *)-1L) {
			struct symbol *n = sym->expansion_trail;

			if (sym->status != STATUS_UNCHANGED) {
				if (!has_changed) {
					print_location();
					fprintf(stderr, "%s: %s: modversion "
						"changed because of changes "
						"in ", flag_preserve ? "error" :
						       "warning", name);
				} else
					fprintf(stderr, ", ");
				print_type_name(sym->type, sym->name);
				if (sym->status == STATUS_DEFINED)
					fprintf(stderr, " (became defined)");
				has_changed = 1;
				if (flag_preserve)
					errors++;
			}
			sym->expansion_trail = 0;
			sym = n;
		}
		if (has_changed)
			fprintf(stderr, "\n");

		if (flag_dump_defs)
			fputs(">\n", debugfile);

		/* Used as a linker script. */
		printf("%s__crc_%s = 0x%08lx ;\n", mod_prefix, name, crc);
	}
}