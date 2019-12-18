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
struct TYPE_2__ {int /*<<< orphan*/  vapi_delay_time; } ;
typedef  TYPE_1__ vapi_additional_info_t ;
typedef  int UWORD ;
typedef  char UBYTE ;

/* Variables and functions */
 int* CommandFrame ; 
 int /*<<< orphan*/ * DataBuffer ; 
 int /*<<< orphan*/  DataIndex ; 
 int ExpectedBytes ; 
 int /*<<< orphan*/  IMAGE_TYPE_VAPI ; 
 int /*<<< orphan*/  Log_print (char*,int,int,int,int,int) ; 
 int POKEY_DELAYED_SERIN_IRQ ; 
 int SECTOR_DELAY ; 
 int /*<<< orphan*/  SIO_ChkSum (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SIO_DriveStatus (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIO_FormatDisk (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SIO_FormatFrame ; 
 int /*<<< orphan*/  SIO_LAST_READ ; 
 int /*<<< orphan*/  SIO_LAST_WRITE ; 
 int SIO_MAX_DRIVES ; 
 int /*<<< orphan*/  SIO_NoFrame ; 
 int /*<<< orphan*/  SIO_ReadFrame ; 
 int /*<<< orphan*/  SIO_ReadSector (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIO_ReadStatusBlock (int,int /*<<< orphan*/ ) ; 
 int SIO_SERIN_INTERVAL ; 
 int /*<<< orphan*/  SIO_SizeOfSector (char,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIO_WriteFrame ; 
 int* SIO_format_sectorcount ; 
 int* SIO_format_sectorsize ; 
 int SIO_last_drive ; 
 int /*<<< orphan*/  SIO_last_op ; 
 int SIO_last_op_time ; 
 int /*<<< orphan*/  TransferStatus ; 
 scalar_t__* additional_info ; 
 int delay_counter ; 
 int /*<<< orphan*/ * image_type ; 

__attribute__((used)) static UBYTE Command_Frame(void)
{
	int unit;
	int sector;
	int realsize;

	sector = CommandFrame[2] | (((UWORD) CommandFrame[3]) << 8);
	unit = CommandFrame[0] - '1';

	if (unit < 0 || unit >= SIO_MAX_DRIVES) {
		/* Unknown device */
		Log_print("Unknown command frame: %02x %02x %02x %02x %02x",
			   CommandFrame[0], CommandFrame[1], CommandFrame[2],
			   CommandFrame[3], CommandFrame[4]);
		TransferStatus = SIO_NoFrame;
		return 0;
	}
	switch (CommandFrame[1]) {
	case 0x4e:				/* Read Status */
#ifdef DEBUG
		Log_print("Read-status frame: %02x %02x %02x %02x %02x",
			CommandFrame[0], CommandFrame[1], CommandFrame[2],
			CommandFrame[3], CommandFrame[4]);
#endif
		DataBuffer[0] = SIO_ReadStatusBlock(unit, DataBuffer + 1);
		DataBuffer[13] = SIO_ChkSum(DataBuffer + 1, 12);
		DataIndex = 0;
		ExpectedBytes = 14;
		TransferStatus = SIO_ReadFrame;
		POKEY_DELAYED_SERIN_IRQ = SIO_SERIN_INTERVAL;
		return 'A';
	case 0x4f:				/* Write status */
#ifdef DEBUG
		Log_print("Write-status frame: %02x %02x %02x %02x %02x",
			CommandFrame[0], CommandFrame[1], CommandFrame[2],
			CommandFrame[3], CommandFrame[4]);
#endif
		ExpectedBytes = 13;
		DataIndex = 0;
		TransferStatus = SIO_WriteFrame;
		return 'A';
	case 0x50:				/* Write */
	case 0x57:
	case 0xD0:				/* xf551 hispeed */
	case 0xD7:
#ifdef DEBUG
		Log_print("Write-sector frame: %02x %02x %02x %02x %02x",
			CommandFrame[0], CommandFrame[1], CommandFrame[2],
			CommandFrame[3], CommandFrame[4]);
#endif
		SIO_SizeOfSector((UBYTE) unit, sector, &realsize, NULL);
		ExpectedBytes = realsize + 1;
		DataIndex = 0;
		TransferStatus = SIO_WriteFrame;
		SIO_last_op = SIO_LAST_WRITE;
		SIO_last_op_time = 10;
		SIO_last_drive = unit + 1;
		return 'A';
	case 0x52:				/* Read */
	case 0xD2:				/* xf551 hispeed */
#ifdef DEBUG
		Log_print("Read-sector frame: %02x %02x %02x %02x %02x",
			CommandFrame[0], CommandFrame[1], CommandFrame[2],
			CommandFrame[3], CommandFrame[4]);
#endif
		SIO_SizeOfSector((UBYTE) unit, sector, &realsize, NULL);
		DataBuffer[0] = SIO_ReadSector(unit, sector, DataBuffer + 1);
		DataBuffer[1 + realsize] = SIO_ChkSum(DataBuffer + 1, realsize);
		DataIndex = 0;
		ExpectedBytes = 2 + realsize;
		TransferStatus = SIO_ReadFrame;
		/* wait longer before confirmation because bytes could be lost */
		/* before the buffer was set (see $E9FB & $EA37 in XL-OS) */
		POKEY_DELAYED_SERIN_IRQ = SIO_SERIN_INTERVAL << 2; 
		if (image_type[unit] == IMAGE_TYPE_VAPI) {
			vapi_additional_info_t *info;
			info = (vapi_additional_info_t *)additional_info[unit];
			if (info == NULL)
				POKEY_DELAYED_SERIN_IRQ = SIO_SERIN_INTERVAL << 2; 
			else
				POKEY_DELAYED_SERIN_IRQ = ((info->vapi_delay_time + 114/2) / 114) - 12;
		} 
#ifndef NO_SECTOR_DELAY
		else if (sector == 1) {
			POKEY_DELAYED_SERIN_IRQ += delay_counter;
			delay_counter = SECTOR_DELAY;
		}
		else {
			delay_counter = 0;
		}
#endif
		SIO_last_op = SIO_LAST_READ;
		SIO_last_op_time = 10;
		SIO_last_drive = unit + 1;
		return 'A';
	case 0x53:				/* Status */
#ifdef DEBUG
		Log_print("Status frame: %02x %02x %02x %02x %02x",
			CommandFrame[0], CommandFrame[1], CommandFrame[2],
			CommandFrame[3], CommandFrame[4]);
#endif
		DataBuffer[0] = SIO_DriveStatus(unit, DataBuffer + 1);
		DataBuffer[1 + 4] = SIO_ChkSum(DataBuffer + 1, 4);
		DataIndex = 0;
		ExpectedBytes = 6;
		TransferStatus = SIO_ReadFrame;
		POKEY_DELAYED_SERIN_IRQ = SIO_SERIN_INTERVAL;
		return 'A';
	/*case 0x66:*/			/* US Doubler Format - I think! */
	case 0x21:				/* Format Disk */
	case 0xa1:				/* xf551 hispeed */
#ifdef DEBUG
		Log_print("Format-disk frame: %02x %02x %02x %02x %02x",
			CommandFrame[0], CommandFrame[1], CommandFrame[2],
			CommandFrame[3], CommandFrame[4]);
#endif
		realsize = SIO_format_sectorsize[unit];
		DataBuffer[0] = SIO_FormatDisk(unit, DataBuffer + 1, realsize, SIO_format_sectorcount[unit]);
		DataBuffer[1 + realsize] = SIO_ChkSum(DataBuffer + 1, realsize);
		DataIndex = 0;
		ExpectedBytes = 2 + realsize;
		TransferStatus = SIO_FormatFrame;
		POKEY_DELAYED_SERIN_IRQ = SIO_SERIN_INTERVAL;
		return 'A';
	case 0x22:				/* Dual Density Format */
	case 0xa2:				/* xf551 hispeed */
#ifdef DEBUG
		Log_print("Format-Medium frame: %02x %02x %02x %02x %02x",
			CommandFrame[0], CommandFrame[1], CommandFrame[2],
			CommandFrame[3], CommandFrame[4]);
#endif
		DataBuffer[0] = SIO_FormatDisk(unit, DataBuffer + 1, 128, 1040);
		DataBuffer[1 + 128] = SIO_ChkSum(DataBuffer + 1, 128);
		DataIndex = 0;
		ExpectedBytes = 2 + 128;
		TransferStatus = SIO_FormatFrame;
		POKEY_DELAYED_SERIN_IRQ = SIO_SERIN_INTERVAL;
		return 'A';
	default:
		/* Unknown command for a disk drive */
#ifdef DEBUG
		Log_print("Command frame: %02x %02x %02x %02x %02x",
			CommandFrame[0], CommandFrame[1], CommandFrame[2],
			CommandFrame[3], CommandFrame[4]);
#endif
		TransferStatus = SIO_NoFrame;
		return 'E';
	}
}