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
struct scsi_device {int dummy; } ;
struct osd_dev {int /*<<< orphan*/  version; int /*<<< orphan*/  def_timeout; struct scsi_device* scsi_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_DEFAULT_SG_TIMEOUT ; 
 int /*<<< orphan*/  OSD_VER2 ; 
 int /*<<< orphan*/  memset (struct osd_dev*,int /*<<< orphan*/ ,int) ; 

void osd_dev_init(struct osd_dev *osdd, struct scsi_device *scsi_device)
{
	memset(osdd, 0, sizeof(*osdd));
	osdd->scsi_device = scsi_device;
	osdd->def_timeout = BLK_DEFAULT_SG_TIMEOUT;
#ifdef OSD_VER1_SUPPORT
	osdd->version = OSD_VER2;
#endif
	/* TODO: Allocate pools for osd_request attributes ... */
}