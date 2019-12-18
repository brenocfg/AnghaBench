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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint64_t ;
struct sec_action {int copy; int remove; int rename; char* newname; } ;
struct elfcopy {char* debuglink; char* prefix_alloc; char* prefix_sec; char* prefix_sym; int /*<<< orphan*/  flags; int /*<<< orphan*/  strip; int /*<<< orphan*/  srec_len; void* set_start; void* pad_to; int /*<<< orphan*/  fill; void* change_start; void* change_addr; } ;
typedef  void* int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISCARD_LLABEL ; 
 int /*<<< orphan*/  DISCARD_LOCAL ; 
#define  ECP_ADD_GNU_DEBUGLINK 162 
#define  ECP_ADD_SECTION 161 
#define  ECP_CHANGE_ADDR 160 
#define  ECP_CHANGE_SEC_ADDR 159 
#define  ECP_CHANGE_SEC_LMA 158 
#define  ECP_CHANGE_SEC_VMA 157 
#define  ECP_CHANGE_START 156 
#define  ECP_CHANGE_WARN 155 
#define  ECP_GAP_FILL 154 
#define  ECP_GLOBALIZE_SYMBOL 153 
#define  ECP_GLOBALIZE_SYMBOLS 152 
#define  ECP_KEEP_GLOBAL_SYMBOLS 151 
#define  ECP_KEEP_SYMBOLS 150 
#define  ECP_LOCALIZE_HIDDEN 149 
#define  ECP_LOCALIZE_SYMBOLS 148 
#define  ECP_NO_CHANGE_WARN 147 
#define  ECP_ONLY_DEBUG 146 
#define  ECP_ONLY_DWO 145 
#define  ECP_PAD_TO 144 
#define  ECP_PREFIX_ALLOC 143 
#define  ECP_PREFIX_SEC 142 
#define  ECP_PREFIX_SYM 141 
#define  ECP_REDEF_SYMBOL 140 
#define  ECP_REDEF_SYMBOLS 139 
#define  ECP_RENAME_SECTION 138 
#define  ECP_SET_OSABI 137 
#define  ECP_SET_SEC_FLAGS 136 
#define  ECP_SET_START 135 
#define  ECP_SREC_FORCE_S3 134 
#define  ECP_SREC_LEN 133 
#define  ECP_STRIP_DWO 132 
#define  ECP_STRIP_SYMBOLS 131 
#define  ECP_STRIP_UNNEEDED 130 
#define  ECP_WEAKEN_ALL 129 
#define  ECP_WEAKEN_SYMBOLS 128 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  GAP_FILL ; 
 int /*<<< orphan*/  KEEP_GLOBAL ; 
 int /*<<< orphan*/  LOCALIZE_HIDDEN ; 
 int /*<<< orphan*/  NO_CHANGE_WARN ; 
 int /*<<< orphan*/  PRESERVE_DATE ; 
 int /*<<< orphan*/  SEC_COPY ; 
 int /*<<< orphan*/  SEC_REMOVE ; 
 int /*<<< orphan*/  SET_START ; 
 int /*<<< orphan*/  SREC_FORCE_LEN ; 
 int /*<<< orphan*/  SREC_FORCE_S3 ; 
 int /*<<< orphan*/  STRIP_ALL ; 
 int /*<<< orphan*/  STRIP_DEBUG ; 
 int /*<<< orphan*/  STRIP_DWO ; 
 int /*<<< orphan*/  STRIP_NONDEBUG ; 
 int /*<<< orphan*/  STRIP_NONDWO ; 
 int /*<<< orphan*/  STRIP_UNNEEDED ; 
 int /*<<< orphan*/  SYMOP_GLOBALIZE ; 
 int /*<<< orphan*/  SYMOP_KEEP ; 
 int /*<<< orphan*/  SYMOP_KEEPG ; 
 int /*<<< orphan*/  SYMOP_LOCALIZE ; 
 int /*<<< orphan*/  SYMOP_REDEF ; 
 int /*<<< orphan*/  SYMOP_STRIP ; 
 int /*<<< orphan*/  SYMOP_WEAKEN ; 
 int /*<<< orphan*/  WEAKEN_ALL ; 
 int /*<<< orphan*/  WILDCARD ; 
 int /*<<< orphan*/  add_section (struct elfcopy*,char*) ; 
 int /*<<< orphan*/  add_to_symop_list (struct elfcopy*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_file (struct elfcopy*,char const*,char const*) ; 
 int /*<<< orphan*/  elfcopy_longopts ; 
 int /*<<< orphan*/  elfcopy_usage () ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sec_action* lookup_sec_act (struct elfcopy*,char*,int) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  parse_sec_address_op (struct elfcopy*,int,char*,char*) ; 
 int /*<<< orphan*/  parse_sec_flags (struct sec_action*,char*) ; 
 int /*<<< orphan*/  parse_symlist_file (struct elfcopy*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_version () ; 
 int /*<<< orphan*/  set_input_target (struct elfcopy*,char*) ; 
 int /*<<< orphan*/  set_osabi (struct elfcopy*,char*) ; 
 int /*<<< orphan*/  set_output_target (struct elfcopy*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strtoll (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoull (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
elfcopy_main(struct elfcopy *ecp, int argc, char **argv)
{
	struct sec_action	*sac;
	const char		*infile, *outfile;
	char			*fn, *s;
	int			 opt;

	while ((opt = getopt_long(argc, argv, "dB:gG:I:j:K:L:N:O:pR:s:SwW:xXV",
	    elfcopy_longopts, NULL)) != -1) {
		switch(opt) {
		case 'B':
			/* ignored */
			break;
		case 'R':
			sac = lookup_sec_act(ecp, optarg, 1);
			if (sac->copy != 0)
				errx(EXIT_FAILURE,
				    "both copy and remove specified");
			sac->remove = 1;
			ecp->flags |= SEC_REMOVE;
			break;
		case 'S':
			ecp->strip = STRIP_ALL;
			break;
		case 'g':
			ecp->strip = STRIP_DEBUG;
			break;
		case 'G':
			ecp->flags |= KEEP_GLOBAL;
			add_to_symop_list(ecp, optarg, NULL, SYMOP_KEEPG);
			break;
		case 'I':
		case 's':
			set_input_target(ecp, optarg);
			break;
		case 'j':
			sac = lookup_sec_act(ecp, optarg, 1);
			if (sac->remove != 0)
				errx(EXIT_FAILURE,
				    "both copy and remove specified");
			sac->copy = 1;
			ecp->flags |= SEC_COPY;
			break;
		case 'K':
			add_to_symop_list(ecp, optarg, NULL, SYMOP_KEEP);
			break;
		case 'L':
			add_to_symop_list(ecp, optarg, NULL, SYMOP_LOCALIZE);
			break;
		case 'N':
			add_to_symop_list(ecp, optarg, NULL, SYMOP_STRIP);
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
		case 'W':
			add_to_symop_list(ecp, optarg, NULL, SYMOP_WEAKEN);
			break;
		case 'x':
			ecp->flags |= DISCARD_LOCAL;
			break;
		case 'X':
			ecp->flags |= DISCARD_LLABEL;
			break;
		case ECP_ADD_GNU_DEBUGLINK:
			ecp->debuglink = optarg;
			break;
		case ECP_ADD_SECTION:
			add_section(ecp, optarg);
			break;
		case ECP_CHANGE_ADDR:
			ecp->change_addr = (int64_t) strtoll(optarg, NULL, 0);
			break;
		case ECP_CHANGE_SEC_ADDR:
			parse_sec_address_op(ecp, opt, "--change-section-addr",
			    optarg);
			break;
		case ECP_CHANGE_SEC_LMA:
			parse_sec_address_op(ecp, opt, "--change-section-lma",
			    optarg);
			break;
		case ECP_CHANGE_SEC_VMA:
			parse_sec_address_op(ecp, opt, "--change-section-vma",
			    optarg);
			break;
		case ECP_CHANGE_START:
			ecp->change_start = (int64_t) strtoll(optarg, NULL, 0);
			break;
		case ECP_CHANGE_WARN:
			/* default */
			break;
		case ECP_GAP_FILL:
			ecp->fill = (uint8_t) strtoul(optarg, NULL, 0);
			ecp->flags |= GAP_FILL;
			break;
		case ECP_GLOBALIZE_SYMBOL:
			add_to_symop_list(ecp, optarg, NULL, SYMOP_GLOBALIZE);
			break;
		case ECP_GLOBALIZE_SYMBOLS:
			parse_symlist_file(ecp, optarg, SYMOP_GLOBALIZE);
			break;
		case ECP_KEEP_SYMBOLS:
			parse_symlist_file(ecp, optarg, SYMOP_KEEP);
			break;
		case ECP_KEEP_GLOBAL_SYMBOLS:
			parse_symlist_file(ecp, optarg, SYMOP_KEEPG);
			break;
		case ECP_LOCALIZE_HIDDEN:
			ecp->flags |= LOCALIZE_HIDDEN;
			break;
		case ECP_LOCALIZE_SYMBOLS:
			parse_symlist_file(ecp, optarg, SYMOP_LOCALIZE);
			break;
		case ECP_NO_CHANGE_WARN:
			ecp->flags |= NO_CHANGE_WARN;
			break;
		case ECP_ONLY_DEBUG:
			ecp->strip = STRIP_NONDEBUG;
			break;
		case ECP_ONLY_DWO:
			ecp->strip = STRIP_NONDWO;
			break;
		case ECP_PAD_TO:
			ecp->pad_to = (uint64_t) strtoull(optarg, NULL, 0);
			break;
		case ECP_PREFIX_ALLOC:
			ecp->prefix_alloc = optarg;
			break;
		case ECP_PREFIX_SEC:
			ecp->prefix_sec = optarg;
			break;
		case ECP_PREFIX_SYM:
			ecp->prefix_sym = optarg;
			break;
		case ECP_REDEF_SYMBOL:
			if ((s = strchr(optarg, '=')) == NULL)
				errx(EXIT_FAILURE,
				    "illegal format for --redefine-sym");
			*s++ = '\0';
			add_to_symop_list(ecp, optarg, s, SYMOP_REDEF);
			break;
		case ECP_REDEF_SYMBOLS:
			parse_symlist_file(ecp, optarg, SYMOP_REDEF);
			break;
		case ECP_RENAME_SECTION:
			if ((fn = strchr(optarg, '=')) == NULL)
				errx(EXIT_FAILURE,
				    "illegal format for --rename-section");
			*fn++ = '\0';

			/* Check for optional flags. */
			if ((s = strchr(fn, ',')) != NULL)
				*s++ = '\0';

			sac = lookup_sec_act(ecp, optarg, 1);
			sac->rename = 1;
			sac->newname = fn;
			if (s != NULL)
				parse_sec_flags(sac, s);
			break;
		case ECP_SET_OSABI:
			set_osabi(ecp, optarg);
			break;
		case ECP_SET_SEC_FLAGS:
			if ((s = strchr(optarg, '=')) == NULL)
				errx(EXIT_FAILURE,
				    "illegal format for --set-section-flags");
			*s++ = '\0';
			sac = lookup_sec_act(ecp, optarg, 1);
			parse_sec_flags(sac, s);
			break;
		case ECP_SET_START:
			ecp->flags |= SET_START;
			ecp->set_start = (uint64_t) strtoull(optarg, NULL, 0);
			break;
		case ECP_SREC_FORCE_S3:
			ecp->flags |= SREC_FORCE_S3;
			break;
		case ECP_SREC_LEN:
			ecp->flags |= SREC_FORCE_LEN;
			ecp->srec_len = strtoul(optarg, NULL, 0);
			break;
		case ECP_STRIP_DWO:
			ecp->strip = STRIP_DWO;
			break;
		case ECP_STRIP_SYMBOLS:
			parse_symlist_file(ecp, optarg, SYMOP_STRIP);
			break;
		case ECP_STRIP_UNNEEDED:
			ecp->strip = STRIP_UNNEEDED;
			break;
		case ECP_WEAKEN_ALL:
			ecp->flags |= WEAKEN_ALL;
			break;
		case ECP_WEAKEN_SYMBOLS:
			parse_symlist_file(ecp, optarg, SYMOP_WEAKEN);
			break;
		default:
			elfcopy_usage();
		}
	}

	argc -= optind;
	argv += optind;

	if (argc == 0 || argc > 2)
		elfcopy_usage();

	infile = argv[0];
	outfile = NULL;
	if (argc > 1)
		outfile = argv[1];

	create_file(ecp, infile, outfile);
}