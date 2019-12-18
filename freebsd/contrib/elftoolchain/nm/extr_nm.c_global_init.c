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
struct TYPE_4__ {char* def_filename; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int demangle_type; int print_debug; int print_armap; int debug_line; int undef_only; int sort_reverse; int /*<<< orphan*/ * fileargs; int /*<<< orphan*/ * size_print_fn; int /*<<< orphan*/ * value_print_fn; int /*<<< orphan*/ * elem_print_fn; int /*<<< orphan*/ * sort_fn; scalar_t__ no_demangle; scalar_t__ sort_size; scalar_t__ def_only; scalar_t__ print_size; int /*<<< orphan*/  print_name; int /*<<< orphan*/  print_symbol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELFTC_GETPROGNAME () ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 scalar_t__ EV_NONE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  PRINT_NAME_NONE ; 
 int /*<<< orphan*/  PRINT_SYM_SYM ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmp_name ; 
 scalar_t__ elf_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ nm_info ; 
 TYPE_1__ nm_opts ; 
 int /*<<< orphan*/  nm_out_filter ; 
 int /*<<< orphan*/  sym_elem_print_all ; 
 int /*<<< orphan*/  sym_size_dec_print ; 
 int /*<<< orphan*/  sym_value_dec_print ; 

__attribute__((used)) static void
global_init(void)
{

	if (elf_version(EV_CURRENT) == EV_NONE)
		errx(EXIT_FAILURE, "elf_version error");

	nm_info.name = ELFTC_GETPROGNAME();
	nm_info.def_filename = "a.out";
	nm_opts.print_symbol = PRINT_SYM_SYM;
	nm_opts.print_name = PRINT_NAME_NONE;
	nm_opts.demangle_type = -1;
	nm_opts.print_debug = false;
	nm_opts.print_armap = false;
	nm_opts.print_size = 0;
	nm_opts.debug_line = false;
	nm_opts.def_only = 0;
	nm_opts.undef_only = false;
	nm_opts.sort_size = 0;
	nm_opts.sort_reverse = false;
	nm_opts.no_demangle = 0;
	nm_opts.sort_fn = &cmp_name;
	nm_opts.elem_print_fn = &sym_elem_print_all;
	nm_opts.value_print_fn = &sym_value_dec_print;
	nm_opts.size_print_fn = &sym_size_dec_print;
	nm_opts.fileargs = NULL;
	SLIST_INIT(&nm_out_filter);
}