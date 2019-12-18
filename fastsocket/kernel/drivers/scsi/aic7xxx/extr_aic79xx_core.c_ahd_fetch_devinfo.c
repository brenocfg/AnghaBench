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
struct ahd_devinfo {int dummy; } ;
typedef  scalar_t__ role_t ;
typedef  int /*<<< orphan*/  ahd_mode_state ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_MODE_SCSI ; 
 int CMDPHASE_PENDING ; 
 int /*<<< orphan*/  IOWNID ; 
 int OID ; 
 scalar_t__ ROLE_INITIATOR ; 
 scalar_t__ ROLE_TARGET ; 
 int /*<<< orphan*/  SAVED_LUN ; 
 int /*<<< orphan*/  SAVED_SCSIID ; 
 int /*<<< orphan*/  SCSIID_CHANNEL (struct ahd_softc*,int) ; 
 int /*<<< orphan*/  SCSIID_TARGET (struct ahd_softc*,int) ; 
 int /*<<< orphan*/  SEQ_FLAGS ; 
 int /*<<< orphan*/  SSTAT0 ; 
 int TARGET ; 
 int /*<<< orphan*/  TARGIDIN ; 
 int /*<<< orphan*/  TOWNID ; 
 int /*<<< orphan*/  ahd_compile_devinfo (struct ahd_devinfo*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_restore_modes (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_save_modes (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahd_fetch_devinfo(struct ahd_softc *ahd, struct ahd_devinfo *devinfo)
{
	ahd_mode_state	saved_modes;
	u_int		saved_scsiid;
	role_t		role;
	int		our_id;

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);

	if (ahd_inb(ahd, SSTAT0) & TARGET)
		role = ROLE_TARGET;
	else
		role = ROLE_INITIATOR;

	if (role == ROLE_TARGET
	 && (ahd_inb(ahd, SEQ_FLAGS) & CMDPHASE_PENDING) != 0) {
		/* We were selected, so pull our id from TARGIDIN */
		our_id = ahd_inb(ahd, TARGIDIN) & OID;
	} else if (role == ROLE_TARGET)
		our_id = ahd_inb(ahd, TOWNID);
	else
		our_id = ahd_inb(ahd, IOWNID);

	saved_scsiid = ahd_inb(ahd, SAVED_SCSIID);
	ahd_compile_devinfo(devinfo,
			    our_id,
			    SCSIID_TARGET(ahd, saved_scsiid),
			    ahd_inb(ahd, SAVED_LUN),
			    SCSIID_CHANNEL(ahd, saved_scsiid),
			    role);
	ahd_restore_modes(ahd, saved_modes);
}