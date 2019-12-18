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
struct cdrom_tochdr {int cdth_trk0; int cdth_trk1; } ;
struct cdrom_tocentry {int cdte_track; int cdte_ctrl; int /*<<< orphan*/  cdte_format; } ;
struct cdrom_device_info {TYPE_1__* handle; } ;
struct TYPE_2__ {scalar_t__ xa_flag; } ;
typedef  TYPE_1__ Scsi_CD ;

/* Variables and functions */
 int CDROM_DATA_TRACK ; 
 int /*<<< orphan*/  CDROM_LBA ; 
 int CDS_AUDIO ; 
 int CDS_DATA_1 ; 
 int CDS_NO_DISC ; 
 int CDS_NO_INFO ; 
 int CDS_XA_2_1 ; 
 int ENOMEDIUM ; 
 scalar_t__ sr_read_tocentry (struct cdrom_device_info*,struct cdrom_tocentry*) ; 
 int sr_read_tochdr (struct cdrom_device_info*,struct cdrom_tochdr*) ; 

int sr_disk_status(struct cdrom_device_info *cdi)
{
	Scsi_CD *cd = cdi->handle;
	struct cdrom_tochdr toc_h;
	struct cdrom_tocentry toc_e;
	int i, rc, have_datatracks = 0;

	/* look for data tracks */
	rc = sr_read_tochdr(cdi, &toc_h);
	if (rc)
		return (rc == -ENOMEDIUM) ? CDS_NO_DISC : CDS_NO_INFO;

	for (i = toc_h.cdth_trk0; i <= toc_h.cdth_trk1; i++) {
		toc_e.cdte_track = i;
		toc_e.cdte_format = CDROM_LBA;
		if (sr_read_tocentry(cdi, &toc_e))
			return CDS_NO_INFO;
		if (toc_e.cdte_ctrl & CDROM_DATA_TRACK) {
			have_datatracks = 1;
			break;
		}
	}
	if (!have_datatracks)
		return CDS_AUDIO;

	if (cd->xa_flag)
		return CDS_XA_2_1;
	else
		return CDS_DATA_1;
}