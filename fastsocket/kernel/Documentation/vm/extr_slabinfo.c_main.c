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
 int REG_ICASE ; 
 int REG_NOSUB ; 
 int /*<<< orphan*/  alias () ; 
 int /*<<< orphan*/  debug_opt_scan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,char*,...) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getpagesize () ; 
 int /*<<< orphan*/  link_slabs () ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  optopt ; 
 int /*<<< orphan*/  opts ; 
 int /*<<< orphan*/  output_slabs () ; 
 int /*<<< orphan*/  page_size ; 
 int /*<<< orphan*/  pattern ; 
 int /*<<< orphan*/  read_slab_dir () ; 
 int regcomp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  rename_slabs () ; 
 int set_debug ; 
 int show_activity ; 
 int show_alias ; 
 int show_empty ; 
 int show_first_alias ; 
 int show_inverted ; 
 int show_numa ; 
 int show_ops ; 
 int show_report ; 
 int show_single_ref ; 
 int show_slab ; 
 int show_totals ; 
 int show_track ; 
 int shrink ; 
 int /*<<< orphan*/  skip_zero ; 
 int sort_active ; 
 int sort_size ; 
 int /*<<< orphan*/  sort_slabs () ; 
 int /*<<< orphan*/  totals () ; 
 int /*<<< orphan*/  usage () ; 
 int validate ; 

int main(int argc, char *argv[])
{
	int c;
	int err;
	char *pattern_source;

	page_size = getpagesize();

	while ((c = getopt_long(argc, argv, "aAd::Defhil1noprstvzTS",
						opts, NULL)) != -1)
		switch (c) {
		case '1':
			show_single_ref = 1;
			break;
		case 'a':
			show_alias = 1;
			break;
		case 'A':
			sort_active = 1;
			break;
		case 'd':
			set_debug = 1;
			if (!debug_opt_scan(optarg))
				fatal("Invalid debug option '%s'\n", optarg);
			break;
		case 'D':
			show_activity = 1;
			break;
		case 'e':
			show_empty = 1;
			break;
		case 'f':
			show_first_alias = 1;
			break;
		case 'h':
			usage();
			return 0;
		case 'i':
			show_inverted = 1;
			break;
		case 'n':
			show_numa = 1;
			break;
		case 'o':
			show_ops = 1;
			break;
		case 'r':
			show_report = 1;
			break;
		case 's':
			shrink = 1;
			break;
		case 'l':
			show_slab = 1;
			break;
		case 't':
			show_track = 1;
			break;
		case 'v':
			validate = 1;
			break;
		case 'z':
			skip_zero = 0;
			break;
		case 'T':
			show_totals = 1;
			break;
		case 'S':
			sort_size = 1;
			break;

		default:
			fatal("%s: Invalid option '%c'\n", argv[0], optopt);

	}

	if (!show_slab && !show_alias && !show_track && !show_report
		&& !validate && !shrink && !set_debug && !show_ops)
			show_slab = 1;

	if (argc > optind)
		pattern_source = argv[optind];
	else
		pattern_source = ".*";

	err = regcomp(&pattern, pattern_source, REG_ICASE|REG_NOSUB);
	if (err)
		fatal("%s: Invalid pattern '%s' code %d\n",
			argv[0], pattern_source, err);
	read_slab_dir();
	if (show_alias)
		alias();
	else
	if (show_totals)
		totals();
	else {
		link_slabs();
		rename_slabs();
		sort_slabs();
		output_slabs();
	}
	return 0;
}