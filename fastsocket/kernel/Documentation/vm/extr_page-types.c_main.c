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
 int /*<<< orphan*/  describe_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getpagesize () ; 
 int opt_hwpoison ; 
 int opt_list ; 
 int opt_no_summary ; 
 scalar_t__ opt_pid ; 
 int opt_raw ; 
 int opt_unpoison ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  opts ; 
 int /*<<< orphan*/  page_size ; 
 int /*<<< orphan*/  parse_addr_range (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_bits_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_hwpoison_fd () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  show_page_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_summary () ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  walk_addr_ranges () ; 

int main(int argc, char *argv[])
{
	int c;

	page_size = getpagesize();

	while ((c = getopt_long(argc, argv,
				"rp:f:a:b:d:lLNXxh", opts, NULL)) != -1) {
		switch (c) {
		case 'r':
			opt_raw = 1;
			break;
		case 'p':
			parse_pid(optarg);
			break;
		case 'f':
			parse_file(optarg);
			break;
		case 'a':
			parse_addr_range(optarg);
			break;
		case 'b':
			parse_bits_mask(optarg);
			break;
		case 'd':
			describe_flags(optarg);
			exit(0);
		case 'l':
			opt_list = 1;
			break;
		case 'L':
			opt_list = 2;
			break;
		case 'N':
			opt_no_summary = 1;
			break;
		case 'X':
			opt_hwpoison = 1;
			prepare_hwpoison_fd();
			break;
		case 'x':
			opt_unpoison = 1;
			prepare_hwpoison_fd();
			break;
		case 'h':
			usage();
			exit(0);
		default:
			usage();
			exit(1);
		}
	}

	if (opt_list && opt_pid)
		printf("voffset\t");
	if (opt_list == 1)
		printf("offset\tlen\tflags\n");
	if (opt_list == 2)
		printf("offset\tflags\n");

	walk_addr_ranges();

	if (opt_list == 1)
		show_page_range(0, 0, 0);  /* drain the buffer */

	if (opt_no_summary)
		return 0;

	if (opt_list)
		printf("\n\n");

	show_summary();

	return 0;
}