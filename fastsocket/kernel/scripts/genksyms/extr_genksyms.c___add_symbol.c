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
struct symbol {int type; char const* name; int is_declared; int is_extern; int status; scalar_t__ is_override; struct symbol* hash_next; int /*<<< orphan*/ * visited; int /*<<< orphan*/ * expansion_trail; struct string_list* defn; } ;
struct string_list {int dummy; } ;
typedef  enum symbol_type { ____Placeholder_symbol_type } symbol_type ;
typedef  enum symbol_status { ____Placeholder_symbol_status } symbol_status ;

/* Variables and functions */
 unsigned long HASH_BUCKETS ; 
 int STATUS_DEFINED ; 
 int STATUS_MODIFIED ; 
 int STATUS_UNCHANGED ; 
 unsigned long crc32 (char const*) ; 
 int /*<<< orphan*/  debugfile ; 
 scalar_t__ equal_list (struct string_list*,struct string_list*) ; 
 int /*<<< orphan*/  error_with_pos (char*,char const*) ; 
 scalar_t__ flag_debug ; 
 scalar_t__ flag_preserve ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_unknown_symbol (struct symbol*) ; 
 scalar_t__ map_to_ns (int) ; 
 int /*<<< orphan*/  nsyms ; 
 int /*<<< orphan*/  print_list (int /*<<< orphan*/ ,struct string_list*) ; 
 int /*<<< orphan*/  print_location () ; 
 int /*<<< orphan*/  print_type_name (int,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 char** symbol_type_name ; 
 struct symbol** symtab ; 
 struct symbol* xmalloc (int) ; 

__attribute__((used)) static struct symbol *__add_symbol(const char *name, enum symbol_type type,
			    struct string_list *defn, int is_extern,
			    int is_reference)
{
	unsigned long h = crc32(name) % HASH_BUCKETS;
	struct symbol *sym;
	enum symbol_status status = STATUS_UNCHANGED;

	for (sym = symtab[h]; sym; sym = sym->hash_next) {
		if (map_to_ns(sym->type) == map_to_ns(type) &&
		    strcmp(name, sym->name) == 0) {
			if (is_reference)
				/* fall through */ ;
			else if (sym->type == type &&
				 equal_list(sym->defn, defn)) {
				if (!sym->is_declared && sym->is_override) {
					print_location();
					print_type_name(type, name);
					fprintf(stderr, " modversion is "
						"unchanged\n");
				}
				sym->is_declared = 1;
				return sym;
			} else if (!sym->is_declared) {
				if (sym->is_override && flag_preserve) {
					print_location();
					fprintf(stderr, "ignoring ");
					print_type_name(type, name);
					fprintf(stderr, " modversion change\n");
					sym->is_declared = 1;
					return sym;
				} else {
					status = is_unknown_symbol(sym) ?
						STATUS_DEFINED : STATUS_MODIFIED;
				}
			} else {
				error_with_pos("redefinition of %s", name);
				return sym;
			}
			break;
		}
	}

	if (sym) {
		struct symbol **psym;

		for (psym = &symtab[h]; *psym; psym = &(*psym)->hash_next) {
			if (*psym == sym) {
				*psym = sym->hash_next;
				break;
			}
		}
		--nsyms;
	}

	sym = xmalloc(sizeof(*sym));
	sym->name = name;
	sym->type = type;
	sym->defn = defn;
	sym->expansion_trail = NULL;
	sym->visited = NULL;
	sym->is_extern = is_extern;

	sym->hash_next = symtab[h];
	symtab[h] = sym;

	sym->is_declared = !is_reference;
	sym->status = status;
	sym->is_override = 0;

	if (flag_debug) {
		fprintf(debugfile, "Defn for %s %s == <",
			symbol_type_name[type], name);
		if (is_extern)
			fputs("extern ", debugfile);
		print_list(debugfile, defn);
		fputs(">\n", debugfile);
	}

	++nsyms;
	return sym;
}