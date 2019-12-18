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
struct scsi_sense_hdr {int dummy; } ;
struct scsi_disk {struct scsi_device* device; } ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int DRIVER_SENSE ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  SD_FLUSH_TIMEOUT ; 
 int /*<<< orphan*/  SD_MAX_RETRIES ; 
 unsigned char SYNCHRONIZE_CACHE ; 
 int driver_byte (int) ; 
 int /*<<< orphan*/  scsi_device_online (struct scsi_device*) ; 
 int scsi_execute_req (struct scsi_device*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct scsi_sense_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_print_result (struct scsi_disk*,int) ; 
 int /*<<< orphan*/  sd_print_sense_hdr (struct scsi_disk*,struct scsi_sense_hdr*) ; 

__attribute__((used)) static int sd_sync_cache(struct scsi_disk *sdkp)
{
	int retries, res;
	struct scsi_device *sdp = sdkp->device;
	struct scsi_sense_hdr sshdr;

	if (!scsi_device_online(sdp))
		return -ENODEV;


	for (retries = 3; retries > 0; --retries) {
		unsigned char cmd[10] = { 0 };

		cmd[0] = SYNCHRONIZE_CACHE;
		/*
		 * Leave the rest of the command zero to indicate
		 * flush everything.
		 */
		res = scsi_execute_req(sdp, cmd, DMA_NONE, NULL, 0, &sshdr,
				       SD_FLUSH_TIMEOUT, SD_MAX_RETRIES, NULL);
		if (res == 0)
			break;
	}

	if (res) {
		sd_print_result(sdkp, res);
		if (driver_byte(res) & DRIVER_SENSE)
			sd_print_sense_hdr(sdkp, &sshdr);
	}

	if (res)
		return -EIO;
	return 0;
}