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
struct scsi_device {scalar_t__ start_stop_pwr_cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int DRIVER_SENSE ; 
 int ENODEV ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  SD_MAX_RETRIES ; 
 int /*<<< orphan*/  SD_TIMEOUT ; 
 unsigned char START_STOP ; 
 int driver_byte (int) ; 
 int /*<<< orphan*/  scsi_device_online (struct scsi_device*) ; 
 int scsi_execute_req (struct scsi_device*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct scsi_sense_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_print_result (struct scsi_disk*,int) ; 
 int /*<<< orphan*/  sd_print_sense_hdr (struct scsi_disk*,struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*) ; 

__attribute__((used)) static int sd_start_stop_device(struct scsi_disk *sdkp, int start)
{
	unsigned char cmd[6] = { START_STOP };	/* START_VALID */
	struct scsi_sense_hdr sshdr;
	struct scsi_device *sdp = sdkp->device;
	int res;

	if (start)
		cmd[4] |= 1;	/* START */

	if (sdp->start_stop_pwr_cond)
		cmd[4] |= start ? 1 << 4 : 3 << 4;	/* Active or Standby */

	if (!scsi_device_online(sdp))
		return -ENODEV;

	res = scsi_execute_req(sdp, cmd, DMA_NONE, NULL, 0, &sshdr,
			       SD_TIMEOUT, SD_MAX_RETRIES, NULL);
	if (res) {
		sd_printk(KERN_WARNING, sdkp, "START_STOP FAILED\n");
		sd_print_result(sdkp, res);
		if (driver_byte(res) & DRIVER_SENSE)
			sd_print_sense_hdr(sdkp, &sshdr);
	}

	return res;
}