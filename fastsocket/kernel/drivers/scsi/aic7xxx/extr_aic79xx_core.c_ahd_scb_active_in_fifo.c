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
struct scb {int dummy; } ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int CFG4DATA ; 
 int INVALID_ADDR ; 
 scalar_t__ LONGJMP_ADDR ; 
 int SAVEPTRS ; 
 scalar_t__ SCB_GET_TAG (struct scb*) ; 
 scalar_t__ SEQINTSRC ; 
 scalar_t__ ahd_get_scbptr (struct ahd_softc*) ; 
 int ahd_inb (struct ahd_softc*,scalar_t__) ; 

__attribute__((used)) static int
ahd_scb_active_in_fifo(struct ahd_softc *ahd, struct scb *scb)
{

	/*
	 * The FIFO is only active for our transaction if
	 * the SCBPTR matches the SCB's ID and the firmware
	 * has installed a handler for the FIFO or we have
	 * a pending SAVEPTRS or CFG4DATA interrupt.
	 */
	if (ahd_get_scbptr(ahd) != SCB_GET_TAG(scb)
	 || ((ahd_inb(ahd, LONGJMP_ADDR+1) & INVALID_ADDR) != 0
	  && (ahd_inb(ahd, SEQINTSRC) & (CFG4DATA|SAVEPTRS)) == 0))
		return (0);

	return (1);
}