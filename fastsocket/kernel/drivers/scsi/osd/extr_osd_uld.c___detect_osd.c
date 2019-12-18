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
struct scsi_device {int /*<<< orphan*/  request_queue; } ;
struct TYPE_2__ {struct scsi_device* scsi_device; } ;
struct osd_uld_device {TYPE_1__ od; } ;

/* Variables and functions */
 int ENODEV ; 
 int HZ ; 
 int OSD_CAP_LEN ; 
 int /*<<< orphan*/  OSD_DEBUG (char*,struct osd_uld_device*,struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSD_ERR (char*) ; 
 scalar_t__ osd_auto_detect_ver (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  osd_root_object ; 
 int /*<<< orphan*/  osd_sec_init_nosec_doall_caps (char*,int /*<<< orphan*/ *,int,int) ; 
 int scsi_test_unit_ready (struct scsi_device*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __detect_osd(struct osd_uld_device *oud)
{
	struct scsi_device *scsi_device = oud->od.scsi_device;
	char caps[OSD_CAP_LEN];
	int error;

	/* sending a test_unit_ready as first command seems to be needed
	 * by some targets
	 */
	OSD_DEBUG("start scsi_test_unit_ready %p %p %p\n",
			oud, scsi_device, scsi_device->request_queue);
	error = scsi_test_unit_ready(scsi_device, 10*HZ, 5, NULL);
	if (error)
		OSD_ERR("warning: scsi_test_unit_ready failed\n");

	osd_sec_init_nosec_doall_caps(caps, &osd_root_object, false, true);
	if (osd_auto_detect_ver(&oud->od, caps))
		return -ENODEV;

	return 0;
}