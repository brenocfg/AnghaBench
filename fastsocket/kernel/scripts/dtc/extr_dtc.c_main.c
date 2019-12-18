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
struct boot_info {long long boot_cpuid_phys; int /*<<< orphan*/  dt; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DEFAULT_FDT_VERSION ; 
 char* DTC_VERSION ; 
 int EOF ; 
 int /*<<< orphan*/  die (char*,...) ; 
 struct boot_info* dt_from_blob (char const*) ; 
 struct boot_info* dt_from_fs (char const*) ; 
 struct boot_info* dt_from_source (char const*) ; 
 int /*<<< orphan*/  dt_to_asm (int /*<<< orphan*/ *,struct boot_info*,int) ; 
 int /*<<< orphan*/  dt_to_blob (int /*<<< orphan*/ *,struct boot_info*,int) ; 
 int /*<<< orphan*/  dt_to_source (int /*<<< orphan*/ *,struct boot_info*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_fullpaths (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*,char const*) ; 
 int getopt (int,char**,char*) ; 
 void* minsize ; 
 char* optarg ; 
 int optind ; 
 void* padsize ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  process_checks (int,struct boot_info*) ; 
 scalar_t__ quiet ; 
 void* reservenum ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ streq (char const*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 void* strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long long strtoll (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char *argv[])
{
	struct boot_info *bi;
	const char *inform = "dts";
	const char *outform = "dts";
	const char *outname = "-";
	int force = 0, check = 0;
	const char *arg;
	int opt;
	FILE *outf = NULL;
	int outversion = DEFAULT_FDT_VERSION;
	long long cmdline_boot_cpuid = -1;

	quiet      = 0;
	reservenum = 0;
	minsize    = 0;
	padsize    = 0;

	while ((opt = getopt(argc, argv, "hI:O:o:V:R:S:p:fcqb:v")) != EOF) {
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
		case 'R':
			reservenum = strtol(optarg, NULL, 0);
			break;
		case 'S':
			minsize = strtol(optarg, NULL, 0);
			break;
		case 'p':
			padsize = strtol(optarg, NULL, 0);
			break;
		case 'f':
			force = 1;
			break;
		case 'c':
			check = 1;
			break;
		case 'q':
			quiet++;
			break;
		case 'b':
			cmdline_boot_cpuid = strtoll(optarg, NULL, 0);
			break;
		case 'v':
			printf("Version: %s\n", DTC_VERSION);
			exit(0);
		case 'h':
		default:
			usage();
		}
	}

	if (argc > (optind+1))
		usage();
	else if (argc < (optind+1))
		arg = "-";
	else
		arg = argv[optind];

	/* minsize and padsize are mutually exclusive */
	if (minsize && padsize)
		die("Can't set both -p and -S\n");

	fprintf(stderr, "DTC: %s->%s  on file \"%s\"\n",
		inform, outform, arg);

	if (streq(inform, "dts"))
		bi = dt_from_source(arg);
	else if (streq(inform, "fs"))
		bi = dt_from_fs(arg);
	else if(streq(inform, "dtb"))
		bi = dt_from_blob(arg);
	else
		die("Unknown input format \"%s\"\n", inform);

	if (cmdline_boot_cpuid != -1)
		bi->boot_cpuid_phys = cmdline_boot_cpuid;

	fill_fullpaths(bi->dt, "");
	process_checks(force, bi);


	if (streq(outname, "-")) {
		outf = stdout;
	} else {
		outf = fopen(outname, "w");
		if (! outf)
			die("Couldn't open output file %s: %s\n",
			    outname, strerror(errno));
	}

	if (streq(outform, "dts")) {
		dt_to_source(outf, bi);
	} else if (streq(outform, "dtb")) {
		dt_to_blob(outf, bi, outversion);
	} else if (streq(outform, "asm")) {
		dt_to_asm(outf, bi, outversion);
	} else if (streq(outform, "null")) {
		/* do nothing */
	} else {
		die("Unknown output format \"%s\"\n", outform);
	}

	exit(0);
}