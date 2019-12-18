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
typedef  int u_int ;
struct cs {int begin; int end; } ;
struct ahc_softc {scalar_t__ num_critical_sections; int features; int seqctl; int unpause; struct cs* critical_sections; } ;

/* Variables and functions */
 int AHC_DT ; 
 int AHC_MAX_STEPS ; 
 int CLRBUSFREE ; 
 int /*<<< orphan*/  CLRINT ; 
 int CLRSCSIINT ; 
 int /*<<< orphan*/  CLRSINT1 ; 
 int ENBUSFREE ; 
 int FALSE ; 
 int /*<<< orphan*/  HCNTRL ; 
 int /*<<< orphan*/  SEQADDR0 ; 
 int /*<<< orphan*/  SEQADDR1 ; 
 int /*<<< orphan*/  SEQCTL ; 
 int /*<<< orphan*/  SIMODE0 ; 
 int /*<<< orphan*/  SIMODE1 ; 
 int STEP ; 
 int TRUE ; 
 int /*<<< orphan*/  ahc_delay (int) ; 
 int /*<<< orphan*/  ahc_dump_card_state (struct ahc_softc*) ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_is_paused (struct ahc_softc*) ; 
 char* ahc_name (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
ahc_clear_critical_section(struct ahc_softc *ahc)
{
	int	stepping;
	int	steps;
	u_int	simode0;
	u_int	simode1;

	if (ahc->num_critical_sections == 0)
		return;

	stepping = FALSE;
	steps = 0;
	simode0 = 0;
	simode1 = 0;
	for (;;) {
		struct	cs *cs;
		u_int	seqaddr;
		u_int	i;

		seqaddr = ahc_inb(ahc, SEQADDR0)
			| (ahc_inb(ahc, SEQADDR1) << 8);

		/*
		 * Seqaddr represents the next instruction to execute, 
		 * so we are really executing the instruction just
		 * before it.
		 */
		if (seqaddr != 0)
			seqaddr -= 1;
		cs = ahc->critical_sections;
		for (i = 0; i < ahc->num_critical_sections; i++, cs++) {
			
			if (cs->begin < seqaddr && cs->end >= seqaddr)
				break;
		}

		if (i == ahc->num_critical_sections)
			break;

		if (steps > AHC_MAX_STEPS) {
			printf("%s: Infinite loop in critical section\n",
			       ahc_name(ahc));
			ahc_dump_card_state(ahc);
			panic("critical section loop");
		}

		steps++;
		if (stepping == FALSE) {

			/*
			 * Disable all interrupt sources so that the
			 * sequencer will not be stuck by a pausing
			 * interrupt condition while we attempt to
			 * leave a critical section.
			 */
			simode0 = ahc_inb(ahc, SIMODE0);
			ahc_outb(ahc, SIMODE0, 0);
			simode1 = ahc_inb(ahc, SIMODE1);
			if ((ahc->features & AHC_DT) != 0)
				/*
				 * On DT class controllers, we
				 * use the enhanced busfree logic.
				 * Unfortunately we cannot re-enable
				 * busfree detection within the
				 * current connection, so we must
				 * leave it on while single stepping.
				 */
				ahc_outb(ahc, SIMODE1, simode1 & ENBUSFREE);
			else
				ahc_outb(ahc, SIMODE1, 0);
			ahc_outb(ahc, CLRINT, CLRSCSIINT);
			ahc_outb(ahc, SEQCTL, ahc->seqctl | STEP);
			stepping = TRUE;
		}
		if ((ahc->features & AHC_DT) != 0) {
			ahc_outb(ahc, CLRSINT1, CLRBUSFREE);
			ahc_outb(ahc, CLRINT, CLRSCSIINT);
		}
		ahc_outb(ahc, HCNTRL, ahc->unpause);
		while (!ahc_is_paused(ahc))
			ahc_delay(200);
	}
	if (stepping) {
		ahc_outb(ahc, SIMODE0, simode0);
		ahc_outb(ahc, SIMODE1, simode1);
		ahc_outb(ahc, SEQCTL, ahc->seqctl);
	}
}