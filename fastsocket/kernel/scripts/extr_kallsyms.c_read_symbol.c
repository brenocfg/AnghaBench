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
struct sym_entry {char* sym; scalar_t__ len; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  _text ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ is_arm_mapping_symbol (char*) ; 
 char* malloc (scalar_t__) ; 
 scalar_t__ read_symbol_tr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 char symbol_prefix_char ; 
 unsigned char toupper (char) ; 

__attribute__((used)) static int read_symbol(FILE *in, struct sym_entry *s)
{
	char str[500];
	char *sym, stype;
	int rc;

	rc = fscanf(in, "%llx %c %499s\n", &s->addr, &stype, str);
	if (rc != 3) {
		if (rc != EOF) {
			/* skip line */
			fgets(str, 500, in);
		}
		return -1;
	}

	sym = str;
	/* skip prefix char */
	if (symbol_prefix_char && str[0] == symbol_prefix_char)
		sym++;

	/* Ignore most absolute/undefined (?) symbols. */
	if (strcmp(sym, "_text") == 0)
		_text = s->addr;
	else if (read_symbol_tr(sym, s->addr) == 0)
		/* nothing to do */;
	else if (toupper(stype) == 'A')
	{
		/* Keep these useful absolute symbols */
		if (strcmp(sym, "__kernel_syscall_via_break") &&
		    strcmp(sym, "__kernel_syscall_via_epc") &&
		    strcmp(sym, "__kernel_sigtramp") &&
		    strcmp(sym, "__gp"))
			return -1;

	}
	else if (toupper(stype) == 'U' ||
		 is_arm_mapping_symbol(sym))
		return -1;
	/* exclude also MIPS ELF local symbols ($L123 instead of .L123) */
	else if (str[0] == '$')
		return -1;
	/* exclude debugging symbols */
	else if (stype == 'N')
		return -1;

	/* include the type field in the symbol name, so that it gets
	 * compressed together */
	s->len = strlen(str) + 1;
	s->sym = malloc(s->len + 1);
	if (!s->sym) {
		fprintf(stderr, "kallsyms failure: "
			"unable to allocate required amount of memory\n");
		exit(EXIT_FAILURE);
	}
	strcpy((char *)s->sym + 1, str);
	s->sym[0] = stype;

	return 0;
}