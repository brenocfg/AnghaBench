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
struct scsi_disk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  scsi_show_extd_sense (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_show_sense_hdr (struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*) ; 

__attribute__((used)) static void sd_print_sense_hdr(struct scsi_disk *sdkp,
			       struct scsi_sense_hdr *sshdr)
{
	sd_printk(KERN_INFO, sdkp, "");
	scsi_show_sense_hdr(sshdr);
	sd_printk(KERN_INFO, sdkp, "");
	scsi_show_extd_sense(sshdr->asc, sshdr->ascq);
}