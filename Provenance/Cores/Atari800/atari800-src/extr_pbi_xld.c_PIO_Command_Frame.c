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
typedef  int UWORD ;
typedef  char UBYTE ;

/* Variables and functions */
 int* CommandFrame ; 
 int* DataBuffer ; 
 int /*<<< orphan*/  DataIndex ; 
 int ExpectedBytes ; 
 int /*<<< orphan*/  Log_print (char*,...) ; 
 int /*<<< orphan*/  PIO_FormatFrame ; 
 int /*<<< orphan*/  PIO_NoFrame ; 
 int /*<<< orphan*/  PIO_ReadFrame ; 
 int /*<<< orphan*/  PIO_WriteFrame ; 
 int SIO_ChkSum (int /*<<< orphan*/ ,int) ; 
 int SIO_DriveStatus (int,int /*<<< orphan*/ ) ; 
 int SIO_FormatDisk (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SIO_LAST_READ ; 
 int /*<<< orphan*/  SIO_LAST_WRITE ; 
 int SIO_MAX_DRIVES ; 
 int /*<<< orphan*/  SIO_NO_DISK ; 
 int /*<<< orphan*/  SIO_OFF ; 
 int SIO_ReadSector (int,int,int /*<<< orphan*/ ) ; 
 int SIO_ReadStatusBlock (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIO_SizeOfSector (char,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SIO_drive_status ; 
 int* SIO_format_sectorcount ; 
 int* SIO_format_sectorsize ; 
 int SIO_last_drive ; 
 int /*<<< orphan*/  SIO_last_op ; 
 int SIO_last_op_time ; 
 int /*<<< orphan*/  TransferStatus ; 

__attribute__((used)) static UBYTE PIO_Command_Frame(void)
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
		TransferStatus = PIO_NoFrame;
		return 0;
	}
	switch (CommandFrame[1]) {
	case 0x01:
		Log_print("PIO DISK: Set large mode (unimplemented)");
		return 'E';
	case 0x02:
		Log_print("PIO DISK: Set small mode (unimplemented)");
		return 'E';
	case 0x23:
		Log_print("PIO DISK: Drive Diagnostic In (unimplemented)");
		return 'E';
	case 0x24:
		Log_print("PIO DISK: Drive Diagnostic Out (unimplemented)");
		return 'E';
	case 0x4e:				/* Read Status */
#ifdef PBI_DEBUG
		Log_print("PIO DISK: Read-status frame: %02x %02x %02x %02x %02x",
			CommandFrame[0], CommandFrame[1], CommandFrame[2],
			CommandFrame[3], CommandFrame[4]);
#endif
		DataBuffer[0] = SIO_ReadStatusBlock(unit, DataBuffer + 1);
		DataBuffer[13] = SIO_ChkSum(DataBuffer + 1, 12);
		DataIndex = 0;
		ExpectedBytes = 14;
		TransferStatus = PIO_ReadFrame;
		/*DELAYED_SERIN_IRQ = SERIN_INTERVAL;*/
		return 'A';
	case 0x4f:				/* Write status */
#ifdef PBI_DEBUG
		Log_print("PIO DISK: Write-status frame: %02x %02x %02x %02x %02x",
			CommandFrame[0], CommandFrame[1], CommandFrame[2],
			CommandFrame[3], CommandFrame[4]);
#endif
		ExpectedBytes = 13;
		DataIndex = 0;
		TransferStatus = PIO_WriteFrame;
		return 'A';
	case 0x50:				/* Write */
	case 0x57:
#ifdef PBI_DEBUG
		Log_print("PIO DISK: Write-sector frame: %02x %02x %02x %02x %02x",
			CommandFrame[0], CommandFrame[1], CommandFrame[2],
			CommandFrame[3], CommandFrame[4]);
#endif
		SIO_SizeOfSector((UBYTE) unit, sector, &realsize, NULL);
		ExpectedBytes = realsize + 1;
		DataIndex = 0;
		TransferStatus = PIO_WriteFrame;
		SIO_last_op = SIO_LAST_WRITE;
		SIO_last_op_time = 10;
		SIO_last_drive = unit + 1;
		return 'A';
	case 0x52:				/* Read */
#ifdef PBI_DEBUG
		Log_print("PIO DISK: Read-sector frame: %02x %02x %02x %02x %02x",
			CommandFrame[0], CommandFrame[1], CommandFrame[2],
			CommandFrame[3], CommandFrame[4]);
#endif
		SIO_SizeOfSector((UBYTE) unit, sector, &realsize, NULL);
		DataBuffer[0] = SIO_ReadSector(unit, sector, DataBuffer + 1);
		DataBuffer[1 + realsize] = SIO_ChkSum(DataBuffer + 1, realsize);
		DataIndex = 0;
		ExpectedBytes = 2 + realsize;
		TransferStatus = PIO_ReadFrame;
		/* wait longer before confirmation because bytes could be lost */
		/* before the buffer was set (see $E9FB & $EA37 in XL-OS) */
		/*DELAYED_SERIN_IRQ = SERIN_INTERVAL << 2;*/
		/*
#ifndef NO_SECTOR_DELAY
		if (sector == 1) {
			//DELAYED_SERIN_IRQ += delay_counter;
			delay_counter = SECTOR_DELAY;
		}
		else {
			delay_counter = 0;
		}
#endif*/
		SIO_last_op = SIO_LAST_READ;
		SIO_last_op_time = 10;
		SIO_last_drive = unit + 1;
		return 'A';
	case 0x53:				/* Status */
		/*
		from spec doc:
		BYTE 1 - DISK STATUS

		BIT 0 = 1 indicates an invalid
		command frame was receiv-
		ed.
		BIT 1 = 1 indicates an invalid
		data frame was received.
		BIT 2 = 1 indicates an opera-
		tion was unsuccessful.
		BIT 3 = 1 indicates the disk-
		ette is write protected.
		BIT 4 = 1 indicates drive is
		active.
		BITS 5-7 = 100 indicates single
		density format.
		BITS 5-7 = 101 indicates double
		density format.

		BYTE 2 - DISK CONTROLLER HARDWARE
		STATUS

		This byte shall contain the in-
		verted value of the disk con-
		troller hardware status regis-
		ter as of the last operation.
		The hardware status value for
		no errors shall be $FF. A zero
		in any bit position shall indi-
		cate an error. The definition
		of the bit positions shall be:

		BIT 0 = 0 indicates device busy
		BIT 1 = 0 indicates data re-
		quest is full on a read
		operation.
		BIT 2 = 0 indicates data lost
		BIT 3 = 0 indicates CRC error
		BIT 4 = 0 indicates desired
		track and sector not found
		BIT 5 = 0 indicates record
		type/write fault
		BIT 6 NOT USED
		*BIT 7 = 0 indicates device not
		ready (door open)

		BYTES 3 & 4 - TIMEOUT

		These bytes shall contain a
		disk controller provided maxi-
		mum timeout value, in seconds,
		for the worst case command. The
		worst case operation is for a
		disk format command (time TBD
		seconds). Byte 4 is not used,
		currently.*/
		/*****Compare with:******/
/*
   Status Request from Atari 400/800 Technical Reference Notes

   DVSTAT + 0   Command Status
   DVSTAT + 1   Hardware Status
   DVSTAT + 2   Timeout
   DVSTAT + 3   Unused

   Command Status Bits

   Bit 0 = 1 indicates an invalid command frame was received(same)
   Bit 1 = 1 indicates an invalid data frame was received(same)
   Bit 2 = 1 indicates that last read/write operation was unsuccessful(same)
   Bit 3 = 1 indicates that the diskette is write protected(same)
   Bit 4 = 1 indicates active/standby(same)

   plus

   Bit 5 = 1 indicates double density
   Bit 7 = 1 indicates dual density disk (1050 format)
 */

#ifdef PBI_DEBUG
		Log_print("PIO DISK: Status frame: %02x %02x %02x %02x %02x",
			CommandFrame[0], CommandFrame[1], CommandFrame[2],
			CommandFrame[3], CommandFrame[4]);
#endif
		/*if (SIO_drive_status[unit]==SIO_OFF) SIO_drive_status[unit]=SIO_NO_DISK;*/
		/*need to modify the line below also for  SIO_OFF==SIO_NO_DISK*/
		DataBuffer[0] = SIO_DriveStatus(unit, DataBuffer + 1);
		DataBuffer[2] = 0xff;/*/1;//SIO_DriveStatus(unit, DataBuffer + 1);*/
		if (SIO_drive_status[unit]==SIO_NO_DISK || SIO_drive_status[unit]==SIO_OFF){
		/*Can't turn 1450XLD drives off, so make SIO_OFF==SIO_NO_DISK*/
			DataBuffer[2]=0x7f;
		}
		DataBuffer[1 + 4] = SIO_ChkSum(DataBuffer + 1, 4);
		DataIndex = 0;
		ExpectedBytes = 6;
		TransferStatus = PIO_ReadFrame;
		/*DELAYED_SERIN_IRQ = SERIN_INTERVAL;*/
		return 'A';
	case 0x21:				/* Format Disk */
#ifdef PBI_DEBUG
		Log_print("PIO DISK: Format-disk frame: %02x %02x %02x %02x %02x",
			CommandFrame[0], CommandFrame[1], CommandFrame[2],
			CommandFrame[3], CommandFrame[4]);
#endif
		realsize = SIO_format_sectorsize[unit];
		DataBuffer[0] = SIO_FormatDisk(unit, DataBuffer + 1, realsize, SIO_format_sectorcount[unit]);
		DataBuffer[1 + realsize] = SIO_ChkSum(DataBuffer + 1, realsize);
		DataIndex = 0;
		ExpectedBytes = 2 + realsize;
		TransferStatus = PIO_FormatFrame;
		/*DELAYED_SERIN_IRQ = SERIN_INTERVAL;*/
		return 'A';
	case 0x22:				/* Dual Density Format */
#ifdef PBI_DEBUG
		Log_print("PIO DISK: Format-Medium frame: %02x %02x %02x %02x %02x",
			CommandFrame[0], CommandFrame[1], CommandFrame[2],
			CommandFrame[3], CommandFrame[4]);
#endif
		DataBuffer[0] = SIO_FormatDisk(unit, DataBuffer + 1, 128, 1040);
		DataBuffer[1 + 128] = SIO_ChkSum(DataBuffer + 1, 128);
		DataIndex = 0;
		ExpectedBytes = 2 + 128;
		TransferStatus = PIO_FormatFrame;
		/*DELAYED_SERIN_IRQ = SERIN_INTERVAL;*/
		return 'A';

		/*
		The Integral Disk Drive uses COMMAND BYTE $B1 and
			$B2 for internal use. These COMMAND BYTES may not
			be used by any other drivers.*/
	case 0xb1:
		Log_print("PIO DISK: Internal Command 0xb1 (unimplemented)");
		return 'E';
	case 0xb2:
		Log_print("PIO DISK: Internal Command 0xb2 (unimplemented)");
		return 'E';


	default:
		/* Unknown command for a disk drive */
#ifdef PBI_DEBUG
		Log_print("PIO DISK: Unknown Command frame: %02x %02x %02x %02x %02x",
			CommandFrame[0], CommandFrame[1], CommandFrame[2],
			CommandFrame[3], CommandFrame[4]);
#endif
		TransferStatus = PIO_NoFrame;
		return 'E';
	}
}