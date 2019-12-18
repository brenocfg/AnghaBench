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
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void genksyms_usage(void)
{
	fputs("Usage:\n" "genksyms [-adDTwqhV] > /path/to/.tmp_obj.ver\n" "\n"
#ifdef __GNU_LIBRARY__
	      "  -a, --arch            Select architecture\n"
	      "  -d, --debug           Increment the debug level (repeatable)\n"
	      "  -D, --dump            Dump expanded symbol defs (for debugging only)\n"
	      "  -r, --reference file  Read reference symbols from a file\n"
	      "  -T, --dump-types file Dump expanded types into file\n"
	      "  -p, --preserve        Preserve reference modversions or fail\n"
	      "  -w, --warnings        Enable warnings\n"
	      "  -q, --quiet           Disable warnings (default)\n"
	      "  -h, --help            Print this message\n"
	      "  -V, --version         Print the release version\n"
#else				/* __GNU_LIBRARY__ */
	      "  -a                    Select architecture\n"
	      "  -d                    Increment the debug level (repeatable)\n"
	      "  -D                    Dump expanded symbol defs (for debugging only)\n"
	      "  -r file               Read reference symbols from a file\n"
	      "  -T file               Dump expanded types into file\n"
	      "  -p                    Preserve reference modversions or fail\n"
	      "  -w                    Enable warnings\n"
	      "  -q                    Disable warnings (default)\n"
	      "  -h                    Print this message\n"
	      "  -V                    Print the release version\n"
#endif				/* __GNU_LIBRARY__ */
	      , stderr);
}