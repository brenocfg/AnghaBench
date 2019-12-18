#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* sec_stat_buff; } ;
typedef  TYPE_1__ vapi_additional_info_t ;
typedef  int UBYTE ;

/* Variables and functions */
 scalar_t__ BINLOAD_start_binloading ; 
 scalar_t__ IMAGE_TYPE_PRO ; 
 scalar_t__ IMAGE_TYPE_VAPI ; 
 int /*<<< orphan*/  Log_print (char*,...) ; 
 scalar_t__ SIO_NO_DISK ; 
 scalar_t__ SIO_OFF ; 
 scalar_t__ SIO_READ_ONLY ; 
 scalar_t__* SIO_drive_status ; 
 int* SIO_format_sectorcount ; 
 int* SIO_format_sectorsize ; 
 int /*<<< orphan*/  SeekSector (int,int) ; 
 scalar_t__* additional_info ; 
 int /*<<< orphan*/ ** disk ; 
 int fread (int*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__* image_type ; 
 int* io_success ; 

int SIO_DriveStatus(int unit, UBYTE *buffer)
{
	if (BINLOAD_start_binloading) {
		buffer[0] = 16 + 8;
		buffer[1] = 255;
		buffer[2] = 1;
		buffer[3] = 0 ;
		return 'C';
	}

	if (SIO_drive_status[unit] == SIO_OFF)
		return 0;

	/* .PRO contains status information in the sector header */
	if (io_success[unit] != 0  && image_type[unit] == IMAGE_TYPE_PRO) {
		int sector = io_success[unit];
		SeekSector(unit, sector);
		if (fread(buffer, 1, 4, disk[unit]) < 4) {
			Log_print("SIO_DriveStatus: failed to read sector header");
		}
		return 'C';
	}
	else if (io_success[unit] != 0  && image_type[unit] == IMAGE_TYPE_VAPI &&
			 SIO_drive_status[unit] != SIO_NO_DISK) {
		vapi_additional_info_t *info;
		info = (vapi_additional_info_t *)additional_info[unit];
		buffer[0] = info->sec_stat_buff[0];
		buffer[1] = info->sec_stat_buff[1];
		buffer[2] = info->sec_stat_buff[2];
		buffer[3] = info->sec_stat_buff[3];
		Log_print("Drive Status unit %d %x %x %x %x",unit,buffer[0], buffer[1], buffer[2], buffer[3]);
		return 'C';
	}	
	buffer[0] = 16;         /* drive active */
	buffer[1] = disk[unit] != NULL ? 255 /* WD 177x OK */ : 127 /* no disk */;
	if (io_success[unit] != 0)
		buffer[0] |= 4;     /* failed RW-operation */
	if (SIO_drive_status[unit] == SIO_READ_ONLY)
		buffer[0] |= 8;     /* write protection */
	if (SIO_format_sectorsize[unit] == 256)
		buffer[0] |= 32;    /* double density */
	if (SIO_format_sectorcount[unit] == 1040)
		buffer[0] |= 128;   /* 1050 enhanced density */
	buffer[2] = 1;
	buffer[3] = 0;
	return 'C';
}