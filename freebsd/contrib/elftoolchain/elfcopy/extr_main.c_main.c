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
struct elfcopy {int abi; int nos; char* progname; int /*<<< orphan*/  v_sec; int /*<<< orphan*/  v_arobj; int /*<<< orphan*/  v_symfile; int /*<<< orphan*/  v_symop; int /*<<< orphan*/  v_sadd; int /*<<< orphan*/  v_sac; int /*<<< orphan*/  v_seg; scalar_t__ fill; int /*<<< orphan*/  oed; int /*<<< orphan*/  oec; int /*<<< orphan*/  iec; int /*<<< orphan*/  otf; int /*<<< orphan*/  itf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELFCLASSNONE ; 
 int /*<<< orphan*/  ELFDATANONE ; 
 char* ELFTC_GETPROGNAME () ; 
 int /*<<< orphan*/  ETF_ELF ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 scalar_t__ EV_NONE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct elfcopy* calloc (int,int) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 scalar_t__ elf_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elfcopy_main (struct elfcopy*,int,char**) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct elfcopy*) ; 
 int /*<<< orphan*/  free_sec_act (struct elfcopy*) ; 
 int /*<<< orphan*/  free_sec_add (struct elfcopy*) ; 
 int /*<<< orphan*/  mcs_main (struct elfcopy*,int,char**) ; 
 int /*<<< orphan*/  strip_main (struct elfcopy*,int,char**) ; 
 scalar_t__ strrcmp (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char **argv)
{
	struct elfcopy *ecp;

	if (elf_version(EV_CURRENT) == EV_NONE)
		errx(EXIT_FAILURE, "ELF library initialization failed: %s",
		    elf_errmsg(-1));

	ecp = calloc(1, sizeof(*ecp));
	if (ecp == NULL)
		err(EXIT_FAILURE, "calloc failed");

	ecp->itf = ecp->otf = ETF_ELF;
	ecp->iec = ecp->oec = ELFCLASSNONE;
	ecp->oed = ELFDATANONE;
	ecp->abi = -1;
	/* There is always an empty section. */
	ecp->nos = 1;
	ecp->fill = 0;

	STAILQ_INIT(&ecp->v_seg);
	STAILQ_INIT(&ecp->v_sac);
	STAILQ_INIT(&ecp->v_sadd);
	STAILQ_INIT(&ecp->v_symop);
	STAILQ_INIT(&ecp->v_symfile);
	STAILQ_INIT(&ecp->v_arobj);
	TAILQ_INIT(&ecp->v_sec);

	if ((ecp->progname = ELFTC_GETPROGNAME()) == NULL)
		ecp->progname = "elfcopy";

	if (strrcmp(ecp->progname, "strip") == 0)
		strip_main(ecp, argc, argv);
	else if (strrcmp(ecp->progname, "mcs") == 0)
		mcs_main(ecp, argc, argv);
	else {
		if (strrcmp(ecp->progname, "elfcopy") != 0 &&
		    strrcmp(ecp->progname, "objcopy") != 0)
			warnx("program mode not known, defaulting to elfcopy");
		elfcopy_main(ecp, argc, argv);
	}

	free_sec_add(ecp);
	free_sec_act(ecp);
	free(ecp);

	exit(EXIT_SUCCESS);
}