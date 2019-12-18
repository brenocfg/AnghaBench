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

/* Variables and functions */
 int /*<<< orphan*/  printk (char const*,...) ; 
 char* scsi_extd_sense_format (unsigned char,unsigned char) ; 
 scalar_t__ strstr (char const*,char*) ; 

void
scsi_show_extd_sense(unsigned char asc, unsigned char ascq)
{
        const char *extd_sense_fmt = scsi_extd_sense_format(asc, ascq);

	if (extd_sense_fmt) {
		if (strstr(extd_sense_fmt, "%x")) {
			printk("Add. Sense: ");
			printk(extd_sense_fmt, ascq);
		} else
			printk("Add. Sense: %s", extd_sense_fmt);
	} else {
		if (asc >= 0x80)
			printk("<<vendor>> ASC=0x%x ASCQ=0x%x", asc,
			       ascq);
		if (ascq >= 0x80)
			printk("ASC=0x%x <<vendor>> ASCQ=0x%x", asc,
			       ascq);
		else
			printk("ASC=0x%x ASCQ=0x%x", asc, ascq);
	}

	printk("\n");
}