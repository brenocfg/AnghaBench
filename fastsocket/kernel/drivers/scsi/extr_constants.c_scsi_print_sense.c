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
struct scsi_sense_hdr {int /*<<< orphan*/  ascq; int /*<<< orphan*/  asc; } ;
struct scsi_cmnd {int /*<<< orphan*/  sense_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*) ; 
 int /*<<< orphan*/  scsi_decode_sense_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  scsi_decode_sense_extras (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  scsi_show_extd_sense (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_show_sense_hdr (struct scsi_sense_hdr*) ; 

void scsi_print_sense(char *name, struct scsi_cmnd *cmd)
{
	struct scsi_sense_hdr sshdr;

	scmd_printk(KERN_INFO, cmd, "");
	scsi_decode_sense_buffer(cmd->sense_buffer, SCSI_SENSE_BUFFERSIZE,
				 &sshdr);
	scsi_show_sense_hdr(&sshdr);
	scsi_decode_sense_extras(cmd->sense_buffer, SCSI_SENSE_BUFFERSIZE,
				 &sshdr);
	scmd_printk(KERN_INFO, cmd, "");
	scsi_show_extd_sense(sshdr.asc, sshdr.ascq);
}