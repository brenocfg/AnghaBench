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
struct ahd_softc {int dummy; } ;
typedef  int /*<<< orphan*/  ahd_mode_state ;

/* Variables and functions */
 int AHD_SHOW_FIFOS ; 
 scalar_t__ CCSGCTL ; 
 int CCSGRESET ; 
 int CLRSHCNT ; 
 scalar_t__ DFFSXFRCTL ; 
 int FETCH_INPROG ; 
 int INVALID_ADDR ; 
 scalar_t__ LONGJMP_ADDR ; 
 int RSTCHN ; 
 scalar_t__ SG_STATE ; 
 int ahd_debug ; 
 int ahd_inb (struct ahd_softc*,scalar_t__) ; 
 char* ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  ahd_restore_modes (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_save_modes (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,int,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 

__attribute__((used)) static void
ahd_clear_fifo(struct ahd_softc *ahd, u_int fifo)
{
	ahd_mode_state	 saved_modes;

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_FIFOS) != 0)
		printf("%s: Clearing FIFO %d\n", ahd_name(ahd), fifo);
#endif
	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, fifo, fifo);
	ahd_outb(ahd, DFFSXFRCTL, RSTCHN|CLRSHCNT);
	if ((ahd_inb(ahd, SG_STATE) & FETCH_INPROG) != 0)
		ahd_outb(ahd, CCSGCTL, CCSGRESET);
	ahd_outb(ahd, LONGJMP_ADDR + 1, INVALID_ADDR);
	ahd_outb(ahd, SG_STATE, 0);
	ahd_restore_modes(ahd, saved_modes);
}