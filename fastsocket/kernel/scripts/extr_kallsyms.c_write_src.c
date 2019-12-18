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
struct TYPE_2__ {int* sym; scalar_t__ addr; int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int KSYM_NAME_LEN ; 
 scalar_t__ _text ; 
 int /*<<< orphan*/ * best_table ; 
 int /*<<< orphan*/ * best_table_len ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (unsigned int*) ; 
 unsigned int* malloc (int) ; 
 int /*<<< orphan*/  output_label (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char*) ; 
 TYPE_1__* table ; 
 unsigned int table_cnt ; 
 char toupper (int) ; 

__attribute__((used)) static void write_src(void)
{
	unsigned int i, k, off;
	unsigned int best_idx[256];
	unsigned int *markers;
	char buf[KSYM_NAME_LEN];

	printf("#include <asm/types.h>\n");
	printf("#if BITS_PER_LONG == 64\n");
	printf("#define PTR .quad\n");
	printf("#define ALGN .align 8\n");
	printf("#else\n");
	printf("#define PTR .long\n");
	printf("#define ALGN .align 4\n");
	printf("#endif\n");

	printf("\t.section .rodata, \"a\"\n");

	/* Provide proper symbols relocatability by their '_text'
	 * relativeness.  The symbol names cannot be used to construct
	 * normal symbol references as the list of symbols contains
	 * symbols that are declared static and are private to their
	 * .o files.  This prevents .tmp_kallsyms.o or any other
	 * object from referencing them.
	 */
	output_label("kallsyms_addresses");
	for (i = 0; i < table_cnt; i++) {
		if (toupper(table[i].sym[0]) != 'A') {
			if (_text <= table[i].addr)
				printf("\tPTR\t_text + %#llx\n",
					table[i].addr - _text);
			else
				printf("\tPTR\t_text - %#llx\n",
					_text - table[i].addr);
		} else {
			printf("\tPTR\t%#llx\n", table[i].addr);
		}
	}
	printf("\n");

	output_label("kallsyms_num_syms");
	printf("\tPTR\t%d\n", table_cnt);
	printf("\n");

	/* table of offset markers, that give the offset in the compressed stream
	 * every 256 symbols */
	markers = malloc(sizeof(unsigned int) * ((table_cnt + 255) / 256));
	if (!markers) {
		fprintf(stderr, "kallsyms failure: "
			"unable to allocate required memory\n");
		exit(EXIT_FAILURE);
	}

	output_label("kallsyms_names");
	off = 0;
	for (i = 0; i < table_cnt; i++) {
		if ((i & 0xFF) == 0)
			markers[i >> 8] = off;

		printf("\t.byte 0x%02x", table[i].len);
		for (k = 0; k < table[i].len; k++)
			printf(", 0x%02x", table[i].sym[k]);
		printf("\n");

		off += table[i].len + 1;
	}
	printf("\n");

	output_label("kallsyms_markers");
	for (i = 0; i < ((table_cnt + 255) >> 8); i++)
		printf("\tPTR\t%d\n", markers[i]);
	printf("\n");

	free(markers);

	output_label("kallsyms_token_table");
	off = 0;
	for (i = 0; i < 256; i++) {
		best_idx[i] = off;
		expand_symbol(best_table[i], best_table_len[i], buf);
		printf("\t.asciz\t\"%s\"\n", buf);
		off += strlen(buf) + 1;
	}
	printf("\n");

	output_label("kallsyms_token_index");
	for (i = 0; i < 256; i++)
		printf("\t.short\t%d\n", best_idx[i]);
	printf("\n");
}