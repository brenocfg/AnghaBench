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
struct sec_action {int remove; } ;
struct elfcopy {int flags; scalar_t__ strip; } ;

/* Variables and functions */
 int DISCARD_LLABEL ; 
 int DISCARD_LOCAL ; 
#define  ECP_ONLY_DEBUG 129 
#define  ECP_STRIP_UNNEEDED 128 
 int PRESERVE_DATE ; 
 int SEC_REMOVE ; 
 void* STRIP_ALL ; 
 scalar_t__ STRIP_DEBUG ; 
 scalar_t__ STRIP_NONDEBUG ; 
 scalar_t__ STRIP_UNNEEDED ; 
 int /*<<< orphan*/  SYMOP_KEEP ; 
 int /*<<< orphan*/  SYMOP_STRIP ; 
 int WILDCARD ; 
 int /*<<< orphan*/  add_to_symop_list (struct elfcopy*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_file (struct elfcopy*,char*,char const*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sec_action* lookup_sec_act (struct elfcopy*,char*,int) ; 
 int /*<<< orphan*/ * lookup_symop_list (struct elfcopy*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  print_version () ; 
 int /*<<< orphan*/  set_output_target (struct elfcopy*,char*) ; 
 int /*<<< orphan*/  strip_longopts ; 
 int /*<<< orphan*/  strip_usage () ; 

__attribute__((used)) static void
strip_main(struct elfcopy *ecp, int argc, char **argv)
{
	struct sec_action	*sac;
	const char		*outfile;
	int			 opt;
	int			 i;

	outfile = NULL;
	while ((opt = getopt_long(argc, argv, "hI:K:N:o:O:pR:sSdgVxXw",
	    strip_longopts, NULL)) != -1) {
		switch(opt) {
		case 'R':
			sac = lookup_sec_act(ecp, optarg, 1);
			sac->remove = 1;
			ecp->flags |= SEC_REMOVE;
			break;
		case 's':
			ecp->strip = STRIP_ALL;
			break;
		case 'S':
		case 'g':
		case 'd':
			ecp->strip = STRIP_DEBUG;
			break;
		case 'I':
			/* ignored */
			break;
		case 'K':
			add_to_symop_list(ecp, optarg, NULL, SYMOP_KEEP);
			break;
		case 'N':
			add_to_symop_list(ecp, optarg, NULL, SYMOP_STRIP);
			break;
		case 'o':
			outfile = optarg;
			break;
		case 'O':
			set_output_target(ecp, optarg);
			break;
		case 'p':
			ecp->flags |= PRESERVE_DATE;
			break;
		case 'V':
			print_version();
			break;
		case 'w':
			ecp->flags |= WILDCARD;
			break;
		case 'x':
			ecp->flags |= DISCARD_LOCAL;
			break;
		case 'X':
			ecp->flags |= DISCARD_LLABEL;
			break;
		case ECP_ONLY_DEBUG:
			ecp->strip = STRIP_NONDEBUG;
			break;
		case ECP_STRIP_UNNEEDED:
			ecp->strip = STRIP_UNNEEDED;
			break;
		case 'h':
		default:
			strip_usage();
		}
	}

	argc -= optind;
	argv += optind;

	if (ecp->strip == 0 &&
	    ((ecp->flags & DISCARD_LOCAL) == 0) &&
	    ((ecp->flags & DISCARD_LLABEL) == 0) &&
	    lookup_symop_list(ecp, NULL, SYMOP_STRIP) == NULL)
		ecp->strip = STRIP_ALL;
	if (argc == 0)
		strip_usage();
	/*
	 * Only accept a single input file if an output file had been
	 * specified.
	 */
	if (outfile != NULL && argc != 1)
		strip_usage();

	for (i = 0; i < argc; i++)
		create_file(ecp, argv[i], outfile);
}