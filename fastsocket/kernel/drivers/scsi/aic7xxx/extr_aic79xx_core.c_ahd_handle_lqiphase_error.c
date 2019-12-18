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

/* Variables and functions */
 int /*<<< orphan*/  AHD_MODE_SCSI ; 
 int ATNO ; 
 int /*<<< orphan*/  CLRINT ; 
 int /*<<< orphan*/  CLRLQIINT1 ; 
 int CLRSCSIINT ; 
 int DLZERO ; 
 int /*<<< orphan*/  LQCTL2 ; 
 int LQIPHASE_LQ ; 
 int LQIPHASE_NLQ ; 
 int LQIRETRY ; 
 int /*<<< orphan*/  MDFFSTAT ; 
 int /*<<< orphan*/  SCSISIGO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ahd_dump_card_state (struct ahd_softc*) ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahd_reset_channel (struct ahd_softc*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_active_fifo (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_unpause (struct ahd_softc*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
ahd_handle_lqiphase_error(struct ahd_softc *ahd, u_int lqistat1)
{
	/*
	 * Clear the sources of the interrupts.
	 */
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	ahd_outb(ahd, CLRLQIINT1, lqistat1);

	/*
	 * If the "illegal" phase changes were in response
	 * to our ATN to flag a CRC error, AND we ended up
	 * on packet boundaries, clear the error, restart the
	 * LQI manager as appropriate, and go on our merry
	 * way toward sending the message.  Otherwise, reset
	 * the bus to clear the error.
	 */
	ahd_set_active_fifo(ahd);
	if ((ahd_inb(ahd, SCSISIGO) & ATNO) != 0
	 && (ahd_inb(ahd, MDFFSTAT) & DLZERO) != 0) {
		if ((lqistat1 & LQIPHASE_LQ) != 0) {
			printf("LQIRETRY for LQIPHASE_LQ\n");
			ahd_outb(ahd, LQCTL2, LQIRETRY);
		} else if ((lqistat1 & LQIPHASE_NLQ) != 0) {
			printf("LQIRETRY for LQIPHASE_NLQ\n");
			ahd_outb(ahd, LQCTL2, LQIRETRY);
		} else
			panic("ahd_handle_lqiphase_error: No phase errors\n");
		ahd_dump_card_state(ahd);
		ahd_outb(ahd, CLRINT, CLRSCSIINT);
		ahd_unpause(ahd);
	} else {
		printf("Reseting Channel for LQI Phase error\n");
		ahd_dump_card_state(ahd);
		ahd_reset_channel(ahd, 'A', /*Initiate Reset*/TRUE);
	}
}