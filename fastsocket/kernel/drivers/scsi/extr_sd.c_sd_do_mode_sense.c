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
struct scsi_mode_data {int dummy; } ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_MAX_RETRIES ; 
 int /*<<< orphan*/  SD_TIMEOUT ; 
 int scsi_mode_sense (struct scsi_device*,int,int,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_mode_data*,struct scsi_sense_hdr*) ; 

__attribute__((used)) static inline int
sd_do_mode_sense(struct scsi_device *sdp, int dbd, int modepage,
		 unsigned char *buffer, int len, struct scsi_mode_data *data,
		 struct scsi_sense_hdr *sshdr)
{
	return scsi_mode_sense(sdp, dbd, modepage, buffer, len,
			       SD_TIMEOUT, SD_MAX_RETRIES, data,
			       sshdr);
}