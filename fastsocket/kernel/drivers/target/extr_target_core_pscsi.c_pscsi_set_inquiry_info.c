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
struct t10_wwn {int /*<<< orphan*/ * revision; int /*<<< orphan*/ * model; int /*<<< orphan*/ * vendor; } ;
struct scsi_device {scalar_t__ inquiry_len; unsigned char* inquiry; } ;

/* Variables and functions */
 scalar_t__ INQUIRY_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static void
pscsi_set_inquiry_info(struct scsi_device *sdev, struct t10_wwn *wwn)
{
	unsigned char *buf;

	if (sdev->inquiry_len < INQUIRY_LEN)
		return;

	buf = sdev->inquiry;
	if (!buf)
		return;
	/*
	 * Use sdev->inquiry from drivers/scsi/scsi_scan.c:scsi_alloc_sdev()
	 */
	memcpy(&wwn->vendor[0], &buf[8], sizeof(wwn->vendor));
	memcpy(&wwn->model[0], &buf[16], sizeof(wwn->model));
	memcpy(&wwn->revision[0], &buf[32], sizeof(wwn->revision));
}