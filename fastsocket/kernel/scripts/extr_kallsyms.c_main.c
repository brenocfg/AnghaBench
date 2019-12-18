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

/* Variables and functions */
 int all_symbols ; 
 int /*<<< orphan*/  optimize_token_table () ; 
 int /*<<< orphan*/  read_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_symbols () ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char symbol_prefix_char ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  write_src () ; 

int main(int argc, char **argv)
{
	if (argc >= 2) {
		int i;
		for (i = 1; i < argc; i++) {
			if(strcmp(argv[i], "--all-symbols") == 0)
				all_symbols = 1;
			else if (strncmp(argv[i], "--symbol-prefix=", 16) == 0) {
				char *p = &argv[i][16];
				/* skip quote */
				if ((*p == '"' && *(p+2) == '"') || (*p == '\'' && *(p+2) == '\''))
					p++;
				symbol_prefix_char = *p;
			} else
				usage();
		}
	} else if (argc != 1)
		usage();

	read_map(stdin);
	sort_symbols();
	optimize_token_table();
	write_src();

	return 0;
}