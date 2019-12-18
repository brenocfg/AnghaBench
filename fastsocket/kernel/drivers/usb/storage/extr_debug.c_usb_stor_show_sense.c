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
 int /*<<< orphan*/  US_DEBUGP (char*,char const*) ; 
 int /*<<< orphan*/  US_DEBUGPX (char const*,...) ; 
 char* scsi_extd_sense_format (unsigned char,unsigned char) ; 
 char* scsi_sense_key_string (unsigned char) ; 

void usb_stor_show_sense(
		unsigned char key,
		unsigned char asc,
		unsigned char ascq) {

	const char *what, *keystr;

	keystr = scsi_sense_key_string(key);
	what = scsi_extd_sense_format(asc, ascq);

	if (keystr == NULL)
		keystr = "(Unknown Key)";
	if (what == NULL)
		what = "(unknown ASC/ASCQ)";

	US_DEBUGP("%s: ", keystr);
	US_DEBUGPX(what, ascq);
	US_DEBUGPX("\n");
}