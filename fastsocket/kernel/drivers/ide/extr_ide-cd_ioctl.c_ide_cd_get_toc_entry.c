#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cdrom_info {struct atapi_toc* toc; } ;
struct atapi_toc_entry {int dummy; } ;
struct TYPE_4__ {int last_track; int first_track; } ;
struct atapi_toc {TYPE_1__ hdr; struct atapi_toc_entry* ent; } ;
struct TYPE_5__ {int atapi_flags; struct cdrom_info* driver_data; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int CDROM_LEADOUT ; 
 int EINVAL ; 
 int IDE_AFLAG_TOC_VALID ; 

__attribute__((used)) static int ide_cd_get_toc_entry(ide_drive_t *drive, int track,
				struct atapi_toc_entry **ent)
{
	struct cdrom_info *info = drive->driver_data;
	struct atapi_toc *toc = info->toc;
	int ntracks;

	/*
	 * don't serve cached data, if the toc isn't valid
	 */
	if ((drive->atapi_flags & IDE_AFLAG_TOC_VALID) == 0)
		return -EINVAL;

	/* Check validity of requested track number. */
	ntracks = toc->hdr.last_track - toc->hdr.first_track + 1;

	if (toc->hdr.first_track == CDROM_LEADOUT)
		ntracks = 0;

	if (track == CDROM_LEADOUT)
		*ent = &toc->ent[ntracks];
	else if (track < toc->hdr.first_track || track > toc->hdr.last_track)
		return -EINVAL;
	else
		*ent = &toc->ent[track - toc->hdr.first_track];

	return 0;
}