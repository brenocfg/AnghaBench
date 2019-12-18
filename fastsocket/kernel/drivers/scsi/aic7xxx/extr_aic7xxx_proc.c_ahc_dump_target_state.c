#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct scsi_target {int dummy; } ;
struct scsi_device {int dummy; } ;
struct info_str {int dummy; } ;
struct ahc_tmode_tstate {int dummy; } ;
struct ahc_softc {int features; TYPE_1__* platform_data; } ;
struct ahc_initiator_tinfo {int /*<<< orphan*/  curr; int /*<<< orphan*/  goal; int /*<<< orphan*/  user; } ;
struct TYPE_2__ {struct scsi_target** starget; } ;

/* Variables and functions */
 int AHC_NUM_LUNS ; 
 int AHC_TWIN ; 
 int /*<<< orphan*/  ahc_dump_device_state (struct info_str*,struct scsi_device*) ; 
 struct ahc_initiator_tinfo* ahc_fetch_transinfo (struct ahc_softc*,char,size_t,size_t,struct ahc_tmode_tstate**) ; 
 int /*<<< orphan*/  ahc_format_transinfo (struct info_str*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_info (struct info_str*,char*,...) ; 
 struct scsi_device* scsi_device_lookup_by_target (struct scsi_target*,int) ; 

__attribute__((used)) static void
ahc_dump_target_state(struct ahc_softc *ahc, struct info_str *info,
		      u_int our_id, char channel, u_int target_id,
		      u_int target_offset)
{
	struct	scsi_target *starget;
	struct	ahc_initiator_tinfo *tinfo;
	struct	ahc_tmode_tstate *tstate;
	int	lun;

	tinfo = ahc_fetch_transinfo(ahc, channel, our_id,
				    target_id, &tstate);
	if ((ahc->features & AHC_TWIN) != 0)
		copy_info(info, "Channel %c ", channel);
	copy_info(info, "Target %d Negotiation Settings\n", target_id);
	copy_info(info, "\tUser: ");
	ahc_format_transinfo(info, &tinfo->user);
	starget = ahc->platform_data->starget[target_offset];
	if (!starget)
		return;

	copy_info(info, "\tGoal: ");
	ahc_format_transinfo(info, &tinfo->goal);
	copy_info(info, "\tCurr: ");
	ahc_format_transinfo(info, &tinfo->curr);

	for (lun = 0; lun < AHC_NUM_LUNS; lun++) {
		struct scsi_device *sdev;

		sdev = scsi_device_lookup_by_target(starget, lun);

		if (sdev == NULL)
			continue;

		ahc_dump_device_state(info, sdev);
	}
}