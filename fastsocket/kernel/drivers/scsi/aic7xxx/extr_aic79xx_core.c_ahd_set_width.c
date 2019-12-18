#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct ahd_tmode_tstate {int dummy; } ;
struct ahd_softc {int dummy; } ;
struct TYPE_6__ {int width; } ;
struct TYPE_5__ {int width; } ;
struct TYPE_4__ {int width; } ;
struct ahd_initiator_tinfo {TYPE_3__ curr; TYPE_2__ goal; TYPE_1__ user; } ;
struct ahd_devinfo {int target; int /*<<< orphan*/  channel; int /*<<< orphan*/  our_scsiid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_TRANSFER_NEG ; 
 int /*<<< orphan*/  AHD_NEG_TO_GOAL ; 
 int AHD_TRANS_ACTIVE ; 
 int AHD_TRANS_CUR ; 
 int AHD_TRANS_GOAL ; 
 int AHD_TRANS_USER ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 struct ahd_initiator_tinfo* ahd_fetch_transinfo (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ahd_tmode_tstate**) ; 
 char* ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_pause (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_send_async (struct ahd_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_unpause (struct ahd_softc*) ; 
 scalar_t__ ahd_update_neg_request (struct ahd_softc*,struct ahd_devinfo*,struct ahd_tmode_tstate*,struct ahd_initiator_tinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_update_neg_table (struct ahd_softc*,struct ahd_devinfo*,TYPE_3__*) ; 
 int /*<<< orphan*/  ahd_update_pending_scbs (struct ahd_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 

void
ahd_set_width(struct ahd_softc *ahd, struct ahd_devinfo *devinfo,
	      u_int width, u_int type, int paused)
{
	struct	ahd_initiator_tinfo *tinfo;
	struct	ahd_tmode_tstate *tstate;
	u_int	oldwidth;
	int	active;
	int	update_needed;

	active = (type & AHD_TRANS_ACTIVE) == AHD_TRANS_ACTIVE;
	update_needed = 0;
	tinfo = ahd_fetch_transinfo(ahd, devinfo->channel, devinfo->our_scsiid,
				    devinfo->target, &tstate);

	if ((type & AHD_TRANS_USER) != 0)
		tinfo->user.width = width;

	if ((type & AHD_TRANS_GOAL) != 0)
		tinfo->goal.width = width;

	oldwidth = tinfo->curr.width;
	if ((type & AHD_TRANS_CUR) != 0 && oldwidth != width) {

		update_needed++;

		tinfo->curr.width = width;
		ahd_send_async(ahd, devinfo->channel, devinfo->target,
			       CAM_LUN_WILDCARD, AC_TRANSFER_NEG);
		if (bootverbose) {
			printf("%s: target %d using %dbit transfers\n",
			       ahd_name(ahd), devinfo->target,
			       8 * (0x01 << width));
		}
	}

	if ((type & AHD_TRANS_CUR) != 0) {
		if (!paused)
			ahd_pause(ahd);
		ahd_update_neg_table(ahd, devinfo, &tinfo->curr);
		if (!paused)
			ahd_unpause(ahd);
	}

	update_needed += ahd_update_neg_request(ahd, devinfo, tstate,
						tinfo, AHD_NEG_TO_GOAL);
	if (update_needed && active)
		ahd_update_pending_scbs(ahd);

}