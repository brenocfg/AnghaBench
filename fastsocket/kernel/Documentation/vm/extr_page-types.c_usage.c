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
 int ARRAY_SIZE (char**) ; 
 char** page_flag_names ; 
 int /*<<< orphan*/  page_flag_type (unsigned long long) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void usage(void)
{
	int i, j;

	printf(
"page-types [options]\n"
"            -r|--raw                   Raw mode, for kernel developers\n"
"            -d|--describe flags        Describe flags\n"
"            -a|--addr    addr-spec     Walk a range of pages\n"
"            -b|--bits    bits-spec     Walk pages with specified bits\n"
"            -p|--pid     pid           Walk process address space\n"
#if 0 /* planned features */
"            -f|--file    filename      Walk file address space\n"
#endif
"            -l|--list                  Show page details in ranges\n"
"            -L|--list-each             Show page details one by one\n"
"            -N|--no-summary            Don't show summary info\n"
"            -X|--hwpoison              hwpoison pages\n"
"            -x|--unpoison              unpoison pages\n"
"            -h|--help                  Show this usage message\n"
"flags:\n"
"            0x10                       bitfield format, e.g.\n"
"            anon                       bit-name, e.g.\n"
"            0x10,anon                  comma-separated list, e.g.\n"
"addr-spec:\n"
"            N                          one page at offset N (unit: pages)\n"
"            N+M                        pages range from N to N+M-1\n"
"            N,M                        pages range from N to M-1\n"
"            N,                         pages range from N to end\n"
"            ,M                         pages range from 0 to M-1\n"
"bits-spec:\n"
"            bit1,bit2                  (flags & (bit1|bit2)) != 0\n"
"            bit1,bit2=bit1             (flags & (bit1|bit2)) == bit1\n"
"            bit1,~bit2                 (flags & (bit1|bit2)) == bit1\n"
"            =bit1,bit2                 flags == (bit1|bit2)\n"
"bit-names:\n"
	);

	for (i = 0, j = 0; i < ARRAY_SIZE(page_flag_names); i++) {
		if (!page_flag_names[i])
			continue;
		printf("%16s%s", page_flag_names[i] + 2,
				 page_flag_type(1ULL << i));
		if (++j > 3) {
			j = 0;
			putchar('\n');
		}
	}
	printf("\n                                   "
		"(r) raw mode bits  (o) overloaded bits\n");
}