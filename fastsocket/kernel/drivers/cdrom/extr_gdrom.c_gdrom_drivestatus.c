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
struct cdrom_device_info {int dummy; } ;

/* Variables and functions */
 int CDS_DISC_OK ; 
 int CDS_DRIVE_NOT_READY ; 
 int CDS_NO_INFO ; 
 int /*<<< orphan*/  GDROM_ERROR_REG ; 
 char ctrl_inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gdrom_drivestatus(struct cdrom_device_info *cd_info, int ignore)
{
	/* read the sense key */
	char sense = ctrl_inb(GDROM_ERROR_REG);
	sense &= 0xF0;
	if (sense == 0)
		return CDS_DISC_OK;
	if (sense == 0x20)
		return CDS_DRIVE_NOT_READY;
	/* default */
	return CDS_NO_INFO;
}