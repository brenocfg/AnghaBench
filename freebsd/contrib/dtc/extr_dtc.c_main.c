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
struct dt_info {char const* outname; long long boot_cpuid_phys; int dtsflags; int /*<<< orphan*/  dt; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DEFAULT_FDT_VERSION ; 
 int DTSF_PLUGIN ; 
 int EOF ; 
 int /*<<< orphan*/  PHANDLE_BOTH ; 
 int /*<<< orphan*/  PHANDLE_EPAPR ; 
 int /*<<< orphan*/  PHANDLE_LEGACY ; 
 char const* alignsize ; 
 int auto_label_aliases ; 
 void* depfile ; 
 int /*<<< orphan*/  die (char*,...) ; 
 struct dt_info* dt_from_blob (char const*) ; 
 struct dt_info* dt_from_fs (char const*) ; 
 struct dt_info* dt_from_source (char const*) ; 
 int /*<<< orphan*/  dt_to_asm (int /*<<< orphan*/ *,struct dt_info*,int) ; 
 int /*<<< orphan*/  dt_to_blob (int /*<<< orphan*/ *,struct dt_info*,int) ; 
 int /*<<< orphan*/  dt_to_source (int /*<<< orphan*/ *,struct dt_info*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (void*) ; 
 int /*<<< orphan*/  fill_fullpaths (int /*<<< orphan*/ ,char*) ; 
 void* fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (void*,char*,char const*) ; 
 int /*<<< orphan*/  fputc (char,void*) ; 
 int generate_fixups ; 
 int /*<<< orphan*/  generate_fixups_tree (struct dt_info*,char*) ; 
 int /*<<< orphan*/  generate_label_tree (struct dt_info*,char*,int) ; 
 int /*<<< orphan*/  generate_local_fixups_tree (struct dt_info*,char*) ; 
 int generate_symbols ; 
 char* guess_input_format (char const*,char*) ; 
 char* guess_type_by_name (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_power_of_2 (char const*) ; 
 void* minsize ; 
 char const* optarg ; 
 int optind ; 
 void* padsize ; 
 int /*<<< orphan*/  parse_checks_option (int,int,char const*) ; 
 int /*<<< orphan*/  phandle_format ; 
 int /*<<< orphan*/  process_checks (int,struct dt_info*) ; 
 scalar_t__ quiet ; 
 void* reservenum ; 
 int /*<<< orphan*/  sort_tree (struct dt_info*) ; 
 int /*<<< orphan*/  srcfile_add_search_path (char const*) ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ streq (char const*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 void* strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long long strtoll (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 
 int util_getopt_long () ; 
 int /*<<< orphan*/  util_version () ; 

int main(int argc, char *argv[])
{
	struct dt_info *dti;
	const char *inform = NULL;
	const char *outform = NULL;
	const char *outname = "-";
	const char *depname = NULL;
	bool force = false, sort = false;
	const char *arg;
	int opt;
	FILE *outf = NULL;
	int outversion = DEFAULT_FDT_VERSION;
	long long cmdline_boot_cpuid = -1;

	quiet      = 0;
	reservenum = 0;
	minsize    = 0;
	padsize    = 0;
	alignsize  = 0;

	while ((opt = util_getopt_long()) != EOF) {
		switch (opt) {
		case 'I':
			inform = optarg;
			break;
		case 'O':
			outform = optarg;
			break;
		case 'o':
			outname = optarg;
			break;
		case 'V':
			outversion = strtol(optarg, NULL, 0);
			break;
		case 'd':
			depname = optarg;
			break;
		case 'R':
			reservenum = strtol(optarg, NULL, 0);
			break;
		case 'S':
			minsize = strtol(optarg, NULL, 0);
			break;
		case 'p':
			padsize = strtol(optarg, NULL, 0);
			break;
		case 'a':
			alignsize = strtol(optarg, NULL, 0);
			if (!is_power_of_2(alignsize))
				die("Invalid argument \"%d\" to -a option\n",
				    alignsize);
			break;
		case 'f':
			force = true;
			break;
		case 'q':
			quiet++;
			break;
		case 'b':
			cmdline_boot_cpuid = strtoll(optarg, NULL, 0);
			break;
		case 'i':
			srcfile_add_search_path(optarg);
			break;
		case 'v':
			util_version();
		case 'H':
			if (streq(optarg, "legacy"))
				phandle_format = PHANDLE_LEGACY;
			else if (streq(optarg, "epapr"))
				phandle_format = PHANDLE_EPAPR;
			else if (streq(optarg, "both"))
				phandle_format = PHANDLE_BOTH;
			else
				die("Invalid argument \"%s\" to -H option\n",
				    optarg);
			break;

		case 's':
			sort = true;
			break;

		case 'W':
			parse_checks_option(true, false, optarg);
			break;

		case 'E':
			parse_checks_option(false, true, optarg);
			break;

		case '@':
			generate_symbols = 1;
			break;
		case 'A':
			auto_label_aliases = 1;
			break;

		case 'h':
			usage(NULL);
		default:
			usage("unknown option");
		}
	}

	if (argc > (optind+1))
		usage("missing files");
	else if (argc < (optind+1))
		arg = "-";
	else
		arg = argv[optind];

	/* minsize and padsize are mutually exclusive */
	if (minsize && padsize)
		die("Can't set both -p and -S\n");

	if (depname) {
		depfile = fopen(depname, "w");
		if (!depfile)
			die("Couldn't open dependency file %s: %s\n", depname,
			    strerror(errno));
		fprintf(depfile, "%s:", outname);
	}

	if (inform == NULL)
		inform = guess_input_format(arg, "dts");
	if (outform == NULL) {
		outform = guess_type_by_name(outname, NULL);
		if (outform == NULL) {
			if (streq(inform, "dts"))
				outform = "dtb";
			else
				outform = "dts";
		}
	}
	if (streq(inform, "dts"))
		dti = dt_from_source(arg);
	else if (streq(inform, "fs"))
		dti = dt_from_fs(arg);
	else if(streq(inform, "dtb"))
		dti = dt_from_blob(arg);
	else
		die("Unknown input format \"%s\"\n", inform);

	dti->outname = outname;

	if (depfile) {
		fputc('\n', depfile);
		fclose(depfile);
	}

	if (cmdline_boot_cpuid != -1)
		dti->boot_cpuid_phys = cmdline_boot_cpuid;

	fill_fullpaths(dti->dt, "");
	process_checks(force, dti);

	/* on a plugin, generate by default */
	if (dti->dtsflags & DTSF_PLUGIN) {
		generate_fixups = 1;
	}

	if (auto_label_aliases)
		generate_label_tree(dti, "aliases", false);

	if (generate_symbols)
		generate_label_tree(dti, "__symbols__", true);

	if (generate_fixups) {
		generate_fixups_tree(dti, "__fixups__");
		generate_local_fixups_tree(dti, "__local_fixups__");
	}

	if (sort)
		sort_tree(dti);

	if (streq(outname, "-")) {
		outf = stdout;
	} else {
		outf = fopen(outname, "wb");
		if (! outf)
			die("Couldn't open output file %s: %s\n",
			    outname, strerror(errno));
	}

	if (streq(outform, "dts")) {
		dt_to_source(outf, dti);
	} else if (streq(outform, "dtb")) {
		dt_to_blob(outf, dti, outversion);
	} else if (streq(outform, "asm")) {
		dt_to_asm(outf, dti, outversion);
	} else if (streq(outform, "null")) {
		/* do nothing */
	} else {
		die("Unknown output format \"%s\"\n", outform);
	}

	exit(0);
}