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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_int ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_ASSERT_MODES (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AHD_MODE_SCSI_MSK ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  SEEADR ; 
 int /*<<< orphan*/  SEECTL ; 
 int /*<<< orphan*/  SEEDAT ; 
 int SEEOP_EWDS ; 
 int SEEOP_EWDS_ADDR ; 
 int SEEOP_EWEN ; 
 int SEEOP_EWEN_ADDR ; 
 int SEEOP_WRITE ; 
 int SEESTART ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahd_outw (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ahd_wait_seeprom (struct ahd_softc*) ; 

int
ahd_write_seeprom(struct ahd_softc *ahd, uint16_t *buf,
		  u_int start_addr, u_int count)
{
	u_int cur_addr;
	u_int end_addr;
	int   error;
	int   retval;

	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	error = ENOENT;

	/* Place the chip into write-enable mode */
	ahd_outb(ahd, SEEADR, SEEOP_EWEN_ADDR);
	ahd_outb(ahd, SEECTL, SEEOP_EWEN | SEESTART);
	error = ahd_wait_seeprom(ahd);
	if (error)
		return (error);

	/*
	 * Write the data.  If we don't get throught the loop at
	 * least once, the arguments were invalid.
	 */
	retval = EINVAL;
	end_addr = start_addr + count;
	for (cur_addr = start_addr; cur_addr < end_addr; cur_addr++) {
		ahd_outw(ahd, SEEDAT, *buf++);
		ahd_outb(ahd, SEEADR, cur_addr);
		ahd_outb(ahd, SEECTL, SEEOP_WRITE | SEESTART);
		
		retval = ahd_wait_seeprom(ahd);
		if (retval)
			break;
	}

	/*
	 * Disable writes.
	 */
	ahd_outb(ahd, SEEADR, SEEOP_EWDS_ADDR);
	ahd_outb(ahd, SEECTL, SEEOP_EWDS | SEESTART);
	error = ahd_wait_seeprom(ahd);
	if (error)
		return (error);
	return (retval);
}