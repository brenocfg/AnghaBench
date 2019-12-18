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
 int /*<<< orphan*/  CDROM_DRIVE_STATUS ; 
 int /*<<< orphan*/  CDSL_CURRENT ; 
#define  CDS_DISC_OK 130 
#define  CDS_NO_DISC 129 
#define  CDS_TRAY_OPEN 128 
 int /*<<< orphan*/  hCDROM ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int LinuxCDGetStatus(void) {
	// 0 - CD Present, disc spinning
	// 1 - CD Present, disc not spinning
	// 2 - CD not present
	// 3 - Tray open
	// see ../windows/cd.cc for more info

	int ret = ioctl(hCDROM, CDROM_DRIVE_STATUS, CDSL_CURRENT);
	switch(ret) {
		case CDS_DISC_OK:
			return 0;
		case CDS_NO_DISC:
			return 2;
		case CDS_TRAY_OPEN:
			return 3;
	}

	// guess it's ok to say there's no disc here...
	return 2;
}