#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_9__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ t; int print_size; int /*<<< orphan*/  (* value_print_fn ) (TYPE_1__ const*) ;int /*<<< orphan*/  (* size_print_fn ) (TYPE_1__ const*) ;int /*<<< orphan*/ * sort_fn; } ;
struct TYPE_10__ {int /*<<< orphan*/  st_size; } ;
typedef  TYPE_1__ GElf_Sym ;

/* Variables and functions */
 scalar_t__ ELFCLASS32 ; 
 scalar_t__ IS_UNDEF_SYM_TYPE (char) ; 
 int /*<<< orphan*/  PRINT_DEMANGLED_NAME (char*,char const*) ; 
 scalar_t__ RADIX_HEX ; 
 int /*<<< orphan*/  cmp_size ; 
 scalar_t__ nm_elfclass ; 
 TYPE_9__ nm_opts ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__ const*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__ const*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__ const*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__ const*) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__ const*) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__ const*) ; 

__attribute__((used)) static void
sym_elem_print_all(char type, const char *sec, const GElf_Sym *sym,
    const char *name)
{

	if (sec == NULL || sym == NULL || name == NULL ||
	    nm_opts.value_print_fn == NULL)
		return;

	if (IS_UNDEF_SYM_TYPE(type)) {
		if (nm_opts.t == RADIX_HEX && nm_elfclass == ELFCLASS32)
			printf("%-8s", "");
		else
			printf("%-16s", "");
	} else {
		switch ((nm_opts.sort_fn == & cmp_size ? 2 : 0) +
		    nm_opts.print_size) {
		case 3:
			if (sym->st_size != 0) {
				nm_opts.value_print_fn(sym);
				printf(" ");
				nm_opts.size_print_fn(sym);
			}
			break;

		case 2:
			if (sym->st_size != 0)
				nm_opts.size_print_fn(sym);
			break;

		case 1:
			nm_opts.value_print_fn(sym);
			if (sym->st_size != 0) {
				printf(" ");
				nm_opts.size_print_fn(sym);
			}
			break;

		case 0:
		default:
			nm_opts.value_print_fn(sym);
		}
	}

	printf(" %c ", type);
	PRINT_DEMANGLED_NAME("%s", name);
}