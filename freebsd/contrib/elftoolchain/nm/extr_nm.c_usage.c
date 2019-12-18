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
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 TYPE_1__ nm_info ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
usage(int exitcode)
{

	printf("Usage: %s [options] file ...\
\n  Display symbolic information in file.\n\
\n  Options: \
\n  -A, --print-file-name     Write the full pathname or library name of an\
\n                            object on each line.\
\n  -a, --debug-syms          Display all symbols include debugger-only\
\n                            symbols.", nm_info.name);
	printf("\
\n  -B                        Equivalent to specifying \"--format=bsd\".\
\n  -C, --demangle[=style]    Decode low-level symbol names.\
\n      --no-demangle         Do not demangle low-level symbol names.\
\n  -D, --dynamic             Display only dynamic symbols.\
\n  -e                        Display only global and static symbols.");
	printf("\
\n  -f                        Produce full output (default).\
\n      --format=format       Display output in specific format.  Allowed\
\n                            formats are: \"bsd\", \"posix\" and \"sysv\".\
\n  -g, --extern-only         Display only global symbol information.\
\n  -h, --help                Show this help message.\
\n  -l, --line-numbers        Display filename and linenumber using\
\n                            debugging information.\
\n  -n, --numeric-sort        Sort symbols numerically by value.");
	printf("\
\n  -o                        Write numeric values in octal. Equivalent to\
\n                            specifying \"-t o\".\
\n  -p, --no-sort             Do not sort symbols.\
\n  -P                        Write information in a portable output format.\
\n                            Equivalent to specifying \"--format=posix\".\
\n  -r, --reverse-sort        Reverse the order of the sort.\
\n  -S, --print-size          Print symbol sizes instead values.\
\n  -s, --print-armap         Include an index of archive members.\
\n      --size-sort           Sort symbols by size.");
	printf("\
\n  -t, --radix=format        Write each numeric value in the specified\
\n                            format:\
\n                               d   In decimal,\
\n                               o   In octal,\
\n                               x   In hexadecimal.");
	printf("\
\n  -u, --undefined-only      Display only undefined symbols.\
\n      --defined-only        Display only defined symbols.\
\n  -V, --version             Show the version identifier for %s.\
\n  -v                        Sort output by value.\
\n  -x                        Write numeric values in hexadecimal.\
\n                            Equivalent to specifying \"-t x\".",
	    nm_info.name);
	printf("\n\
\n  The default options are: output in bsd format, use a hexadecimal radix,\
\n  sort by symbol name, do not demangle names.\n");

	exit(exitcode);
}