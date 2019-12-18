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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_relocs (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  print_absolute_relocs () ; 
 int /*<<< orphan*/  print_absolute_symbols () ; 
 int /*<<< orphan*/  read_ehdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_relocs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_shdrs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_strtabs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_symtabs (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char **argv)
{
	int show_absolute_syms, show_absolute_relocs;
	int as_text;
	const char *fname;
	FILE *fp;
	int i;

	show_absolute_syms = 0;
	show_absolute_relocs = 0;
	as_text = 0;
	fname = NULL;
	for (i = 1; i < argc; i++) {
		char *arg = argv[i];
		if (*arg == '-') {
			if (strcmp(argv[1], "--abs-syms") == 0) {
				show_absolute_syms = 1;
				continue;
			}

			if (strcmp(argv[1], "--abs-relocs") == 0) {
				show_absolute_relocs = 1;
				continue;
			}
			else if (strcmp(argv[1], "--text") == 0) {
				as_text = 1;
				continue;
			}
		}
		else if (!fname) {
			fname = arg;
			continue;
		}
		usage();
	}
	if (!fname) {
		usage();
	}
	fp = fopen(fname, "r");
	if (!fp) {
		die("Cannot open %s: %s\n",
			fname, strerror(errno));
	}
	read_ehdr(fp);
	read_shdrs(fp);
	read_strtabs(fp);
	read_symtabs(fp);
	read_relocs(fp);
	if (show_absolute_syms) {
		print_absolute_symbols();
		return 0;
	}
	if (show_absolute_relocs) {
		print_absolute_relocs();
		return 0;
	}
	emit_relocs(as_text);
	return 0;
}