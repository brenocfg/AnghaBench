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
struct module {char* name; scalar_t__ skip; struct module* next; } ;
struct ext_sym_list {char* file; struct ext_sym_list* next; } ;
struct buffer {scalar_t__ pos; } ;

/* Variables and functions */
 struct ext_sym_list* NOFAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_depends (struct buffer*,struct module*,struct module*) ; 
 int /*<<< orphan*/  add_header (struct buffer*,struct module*) ; 
 int /*<<< orphan*/  add_moddevtable (struct buffer*,struct module*) ; 
 int /*<<< orphan*/  add_rheldata (struct buffer*,struct module*) ; 
 int /*<<< orphan*/  add_srcversion (struct buffer*,struct module*) ; 
 int /*<<< orphan*/  add_staging_flag (struct buffer*,char*) ; 
 int add_versions (struct buffer*,struct module*) ; 
 int all_versions ; 
 int /*<<< orphan*/  check_exports (struct module*) ; 
 int cross_build ; 
 int /*<<< orphan*/  exit (int) ; 
 int external_module ; 
 int /*<<< orphan*/  free (struct ext_sym_list*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  malloc (int) ; 
 struct module* modules ; 
 int modversions ; 
 void* optarg ; 
 int optind ; 
 int /*<<< orphan*/  read_dump (char*,int) ; 
 int /*<<< orphan*/  read_markers (char*) ; 
 int /*<<< orphan*/  read_symbols (char*) ; 
 scalar_t__ sec_mismatch_count ; 
 scalar_t__ sec_mismatch_verbose ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  vmlinux_section_warnings ; 
 int /*<<< orphan*/  warn (char*,scalar_t__) ; 
 int warn_unresolved ; 
 int /*<<< orphan*/  write_dump (char*) ; 
 int /*<<< orphan*/  write_if_changed (struct buffer*,char*) ; 
 int /*<<< orphan*/  write_markers (char*) ; 

int main(int argc, char **argv)
{
	struct module *mod;
	struct buffer buf = { };
	char *kernel_read = NULL, *module_read = NULL;
	char *dump_write = NULL;
	char *markers_read = NULL;
	char *markers_write = NULL;
	int opt;
	int err;
	struct ext_sym_list *extsym_iter;
	struct ext_sym_list *extsym_start = NULL;

	while ((opt = getopt(argc, argv, "i:I:e:cmsSo:awM:K:")) != -1) {
		switch (opt) {
		case 'i':
			kernel_read = optarg;
			break;
		case 'I':
			module_read = optarg;
			external_module = 1;
			break;
		case 'c':
			cross_build = 1;
			break;
		case 'e':
			external_module = 1;
			extsym_iter =
			   NOFAIL(malloc(sizeof(*extsym_iter)));
			extsym_iter->next = extsym_start;
			extsym_iter->file = optarg;
			extsym_start = extsym_iter;
			break;
		case 'm':
			modversions = 1;
			break;
		case 'o':
			dump_write = optarg;
			break;
		case 'a':
			all_versions = 1;
			break;
		case 's':
			vmlinux_section_warnings = 0;
			break;
		case 'S':
			sec_mismatch_verbose = 0;
			break;
		case 'w':
			warn_unresolved = 1;
			break;
			case 'M':
				markers_write = optarg;
				break;
			case 'K':
				markers_read = optarg;
				break;
		default:
			exit(1);
		}
	}

	if (kernel_read)
		read_dump(kernel_read, 1);
	if (module_read)
		read_dump(module_read, 0);
	while (extsym_start) {
		read_dump(extsym_start->file, 0);
		extsym_iter = extsym_start->next;
		free(extsym_start);
		extsym_start = extsym_iter;
	}

	while (optind < argc)
		read_symbols(argv[optind++]);

	for (mod = modules; mod; mod = mod->next) {
		if (mod->skip)
			continue;
		check_exports(mod);
	}

	err = 0;

	for (mod = modules; mod; mod = mod->next) {
		char fname[strlen(mod->name) + 10];

		if (mod->skip)
			continue;

		buf.pos = 0;

		add_header(&buf, mod);
		add_staging_flag(&buf, mod->name);
		err |= add_versions(&buf, mod);
		add_depends(&buf, mod, modules);
		add_moddevtable(&buf, mod);
		add_srcversion(&buf, mod);
		add_rheldata(&buf, mod);

		sprintf(fname, "%s.mod.c", mod->name);
		write_if_changed(&buf, fname);
	}

	if (dump_write)
		write_dump(dump_write);
	if (sec_mismatch_count && !sec_mismatch_verbose)
		warn("modpost: Found %d section mismatch(es).\n"
		     "To see full details build your kernel with:\n"
		     "'make CONFIG_DEBUG_SECTION_MISMATCH=y'\n",
		     sec_mismatch_count);

	if (markers_read)
		read_markers(markers_read);

	if (markers_write)
		write_markers(markers_write);

	return err;
}