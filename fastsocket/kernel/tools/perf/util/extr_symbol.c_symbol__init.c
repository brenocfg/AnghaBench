#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct symbol_name_rb_node {int dummy; } ;
struct symbol {int dummy; } ;
struct TYPE_2__ {int initialized; int priv_size; char* field_sep; char* symfs; int /*<<< orphan*/  dso_list; int /*<<< orphan*/  comm_list; int /*<<< orphan*/  kptr_restrict; int /*<<< orphan*/  sym_list_str; int /*<<< orphan*/  sym_list; int /*<<< orphan*/  comm_list_str; int /*<<< orphan*/  dso_list_str; scalar_t__ try_vmlinux_path; scalar_t__ sort_by_name; } ;

/* Variables and functions */
 int PERF_ALIGN (int,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 char* realpath (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ setup_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlist__delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol__elf_init () ; 
 int /*<<< orphan*/  symbol__read_kptr_restrict () ; 
 TYPE_1__ symbol_conf ; 
 scalar_t__ vmlinux_path__init () ; 

int symbol__init(void)
{
	const char *symfs;

	if (symbol_conf.initialized)
		return 0;

	symbol_conf.priv_size = PERF_ALIGN(symbol_conf.priv_size, sizeof(u64));

	symbol__elf_init();

	if (symbol_conf.sort_by_name)
		symbol_conf.priv_size += (sizeof(struct symbol_name_rb_node) -
					  sizeof(struct symbol));

	if (symbol_conf.try_vmlinux_path && vmlinux_path__init() < 0)
		return -1;

	if (symbol_conf.field_sep && *symbol_conf.field_sep == '.') {
		pr_err("'.' is the only non valid --field-separator argument\n");
		return -1;
	}

	if (setup_list(&symbol_conf.dso_list,
		       symbol_conf.dso_list_str, "dso") < 0)
		return -1;

	if (setup_list(&symbol_conf.comm_list,
		       symbol_conf.comm_list_str, "comm") < 0)
		goto out_free_dso_list;

	if (setup_list(&symbol_conf.sym_list,
		       symbol_conf.sym_list_str, "symbol") < 0)
		goto out_free_comm_list;

	/*
	 * A path to symbols of "/" is identical to ""
	 * reset here for simplicity.
	 */
	symfs = realpath(symbol_conf.symfs, NULL);
	if (symfs == NULL)
		symfs = symbol_conf.symfs;
	if (strcmp(symfs, "/") == 0)
		symbol_conf.symfs = "";
	if (symfs != symbol_conf.symfs)
		free((void *)symfs);

	symbol_conf.kptr_restrict = symbol__read_kptr_restrict();

	symbol_conf.initialized = true;
	return 0;

out_free_comm_list:
	strlist__delete(symbol_conf.comm_list);
out_free_dso_list:
	strlist__delete(symbol_conf.dso_list);
	return -1;
}