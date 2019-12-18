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
struct scsi_sense_hdr {int /*<<< orphan*/  ascq; int /*<<< orphan*/  asc; int /*<<< orphan*/  sense_key; } ;
struct scsi_device {int dummy; } ;
struct clariion_dh_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  buffer; int /*<<< orphan*/  sense; scalar_t__ senselen; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLARIION_NAME ; 
 int /*<<< orphan*/  CLARIION_SHORT_TRESPASS ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int SCSI_DH_DEV_UNSUPP ; 
 int SCSI_DH_IO ; 
 int SCSI_DH_OK ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 char* parse_sp_model (struct scsi_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_normalize_sense (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int send_inquiry_cmd (struct scsi_device*,int /*<<< orphan*/ ,struct clariion_dh_data*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int clariion_std_inquiry(struct scsi_device *sdev,
				struct clariion_dh_data *csdev)
{
	int err;
	char *sp_model;

	err = send_inquiry_cmd(sdev, 0, csdev);
	if (err != SCSI_DH_OK && csdev->senselen) {
		struct scsi_sense_hdr sshdr;

		if (scsi_normalize_sense(csdev->sense, SCSI_SENSE_BUFFERSIZE,
					 &sshdr)) {
			sdev_printk(KERN_ERR, sdev, "%s: INQUIRY sense code "
				    "%02x/%02x/%02x\n", CLARIION_NAME,
				    sshdr.sense_key, sshdr.asc, sshdr.ascq);
		}
		err = SCSI_DH_IO;
		goto out;
	}

	sp_model = parse_sp_model(sdev, csdev->buffer);
	if (!sp_model) {
		err = SCSI_DH_DEV_UNSUPP;
		goto out;
	}

	/*
	 * FC Series arrays do not support long trespass
	 */
	if (!strlen(sp_model) || !strncmp(sp_model, "FC",2))
		csdev->flags |= CLARIION_SHORT_TRESPASS;

	sdev_printk(KERN_INFO, sdev,
		    "%s: detected Clariion %s, flags %x\n",
		    CLARIION_NAME, sp_model, csdev->flags);
out:
	return err;
}