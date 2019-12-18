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
struct ahd_softc {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  ahd_mode_state ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_HAD_FIRST_SEL ; 
 int /*<<< orphan*/  AHD_MODE_CFG ; 
 int AHD_SHOW_MISC ; 
 int BYPASSENAB ; 
 int /*<<< orphan*/  DSPDATACTL ; 
 int ENSELDI ; 
 int ENSELDO ; 
 int RCVROFFSTDIS ; 
 int /*<<< orphan*/  SIMODE0 ; 
 int XMITOFFSTDIS ; 
 int ahd_debug ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 char* ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahd_restore_modes (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_save_modes (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
ahd_setup_iocell_workaround(struct ahd_softc *ahd)
{
	ahd_mode_state saved_modes;

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
	ahd_outb(ahd, DSPDATACTL, ahd_inb(ahd, DSPDATACTL)
	       | BYPASSENAB | RCVROFFSTDIS | XMITOFFSTDIS);
	ahd_outb(ahd, SIMODE0, ahd_inb(ahd, SIMODE0) | (ENSELDO|ENSELDI));
#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_MISC) != 0)
		printf("%s: Setting up iocell workaround\n", ahd_name(ahd));
#endif
	ahd_restore_modes(ahd, saved_modes);
	ahd->flags &= ~AHD_HAD_FIRST_SEL;
}