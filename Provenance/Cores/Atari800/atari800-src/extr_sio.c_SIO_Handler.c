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
typedef  void* UWORD ;
typedef  size_t UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ANTIC_ypos ; 
 scalar_t__ BINLOAD_start_binloading ; 
 int /*<<< orphan*/  CASSETTE_AddGap (int) ; 
 int /*<<< orphan*/  CASSETTE_ReadToMemory (void*,int) ; 
 int /*<<< orphan*/  CASSETTE_WriteFromMemory (void*,int) ; 
 int /*<<< orphan*/  CPU_ClrN ; 
 int /*<<< orphan*/  CPU_SetC ; 
 int /*<<< orphan*/  CPU_SetN ; 
 scalar_t__ CPU_regA ; 
 int CPU_regPC ; 
 int CPU_regY ; 
 int /*<<< orphan*/  DataBuffer ; 
 int /*<<< orphan*/  Log_print (char*,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  MEMORY_CopyFromMem (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MEMORY_CopyToMem (int /*<<< orphan*/ ,void*,int) ; 
 int MEMORY_dGetByte (int) ; 
 void* MEMORY_dGetWordAligned (int) ; 
 int /*<<< orphan*/  MEMORY_dPutByte (int,int) ; 
 int /*<<< orphan*/  POKEY_OFFSET_AUDC1 ; 
 int /*<<< orphan*/  POKEY_OFFSET_AUDC2 ; 
 int /*<<< orphan*/  POKEY_OFFSET_AUDC3 ; 
 int /*<<< orphan*/  POKEY_OFFSET_AUDC4 ; 
 int /*<<< orphan*/  POKEY_PutByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECTOR_DELAY ; 
 size_t SIO_DriveStatus (size_t,int /*<<< orphan*/ ) ; 
 size_t SIO_FormatDisk (size_t,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SIO_LAST_READ ; 
 int /*<<< orphan*/  SIO_LAST_WRITE ; 
 size_t SIO_MAX_DRIVES ; 
 scalar_t__ SIO_OFF ; 
 size_t SIO_ReadSector (size_t,int,int /*<<< orphan*/ ) ; 
 size_t SIO_ReadStatusBlock (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIO_SizeOfSector (size_t,int,int*,int /*<<< orphan*/ *) ; 
 size_t SIO_WriteSector (size_t,int,int /*<<< orphan*/ ) ; 
 size_t SIO_WriteStatusBlock (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__* SIO_drive_status ; 
 int* SIO_format_sectorcount ; 
 int* SIO_format_sectorsize ; 
 int SIO_last_drive ; 
 int /*<<< orphan*/  SIO_last_op ; 
 int SIO_last_op_time ; 
 int /*<<< orphan*/  delay_counter ; 
 int /*<<< orphan*/  last_ypos ; 

void SIO_Handler(void)
{
	int sector = MEMORY_dGetWordAligned(0x30a);
	UBYTE unit = (MEMORY_dGetByte(0x300) + MEMORY_dGetByte(0x301) + 0xff ) - 0x31;
	UBYTE result = 0x00;
	UWORD data = MEMORY_dGetWordAligned(0x304);
	int length = MEMORY_dGetWordAligned(0x308);
	int realsize = 0;
	int cmd = MEMORY_dGetByte(0x302);

	if ((unsigned int)MEMORY_dGetByte(0x300) + (unsigned int)MEMORY_dGetByte(0x301) > 0xff) {
		/* carry */
		unit++;
	}
	/* A real atari just adds the bytes and 0xff. The result could wrap.*/
	/* XL OS: E99D: LDA $0300 ADC $0301 ADC #$FF STA 023A */
	/* Disk 1 is ASCII '1' = 0x31 etc */
	/* Disk 1 -> unit = 0 */
	if (MEMORY_dGetByte(0x300) != 0x60 && unit < SIO_MAX_DRIVES && (SIO_drive_status[unit] != SIO_OFF || BINLOAD_start_binloading)) {	/* UBYTE range ! */
#ifdef DEBUG
		Log_print("SIO disk command is %02x %02x %02x %02x %02x   %02x %02x %02x %02x %02x %02x",
			cmd, MEMORY_dGetByte(0x303), MEMORY_dGetByte(0x304), MEMORY_dGetByte(0x305), MEMORY_dGetByte(0x306),
			MEMORY_dGetByte(0x308), MEMORY_dGetByte(0x309), MEMORY_dGetByte(0x30a), MEMORY_dGetByte(0x30b),
			MEMORY_dGetByte(0x30c), MEMORY_dGetByte(0x30d));
#endif
		switch (cmd) {
		case 0x4e:				/* Read Status Block */
			if (12 == length) {
				result = SIO_ReadStatusBlock(unit, DataBuffer);
				if (result == 'C')
					MEMORY_CopyToMem(DataBuffer, data, 12);
			}
			else
				result = 'E';
			break;
		case 0x4f:				/* Write Status Block */
			if (12 == length) {
				MEMORY_CopyFromMem(data, DataBuffer, 12);
				result = SIO_WriteStatusBlock(unit, DataBuffer);
			}
			else
				result = 'E';
			break;
		case 0x50:				/* Write */
		case 0x57:
		case 0xD0:				/* xf551 hispeed */
		case 0xD7:
			SIO_SizeOfSector(unit, sector, &realsize, NULL);
			if (realsize == length) {
				MEMORY_CopyFromMem(data, DataBuffer, realsize);
				result = SIO_WriteSector(unit, sector, DataBuffer);
			}
			else
				result = 'E';
			break;
		case 0x52:				/* Read */
		case 0xD2:				/* xf551 hispeed */
#ifndef NO_SECTOR_DELAY
			if (sector == 1) {
				if (delay_counter > 0) {
					if (last_ypos != ANTIC_ypos) {
						last_ypos = ANTIC_ypos;
						delay_counter--;
					}
					CPU_regPC = 0xe459;	/* stay at SIO patch */
					return;
				}
				delay_counter = SECTOR_DELAY;
			}
			else {
				delay_counter = 0;
			}
#endif
			SIO_SizeOfSector(unit, sector, &realsize, NULL);
			if (realsize == length) {
				result = SIO_ReadSector(unit, sector, DataBuffer);
				if (result == 'C')
					MEMORY_CopyToMem(DataBuffer, data, realsize);
			}
			else
				result = 'E';
			break;
		case 0x53:				/* Status */
			if (4 == length) {
				result = SIO_DriveStatus(unit, DataBuffer);
				if (result == 'C') {
					MEMORY_CopyToMem(DataBuffer, data, 4);
				}
			}
			else
				result = 'E';
			break;
		/*case 0x66:*/			/* US Doubler Format - I think! */
		case 0x21:				/* Format Disk */
		case 0xA1:				/* xf551 hispeed */
			realsize = SIO_format_sectorsize[unit];
			if (realsize == length) {
				result = SIO_FormatDisk(unit, DataBuffer, realsize, SIO_format_sectorcount[unit]);
				if (result == 'C')
					MEMORY_CopyToMem(DataBuffer, data, realsize);
			}
			else {
				/* there are programs which send the format-command but don't wait for the result (eg xf-tools) */
				SIO_FormatDisk(unit, DataBuffer, realsize, SIO_format_sectorcount[unit]);
				result = 'E';
			}
			break;
		case 0x22:				/* Enhanced Density Format */
		case 0xA2:				/* xf551 hispeed */
			realsize = 128;
			if (realsize == length) {
				result = SIO_FormatDisk(unit, DataBuffer, 128, 1040);
				if (result == 'C')
					MEMORY_CopyToMem(DataBuffer, data, realsize);
			}
			else {
				SIO_FormatDisk(unit, DataBuffer, 128, 1040);
				result = 'E';
			}
			break;
		default:
			result = 'N';
		}
	}
	/* cassette i/o */
	else if (MEMORY_dGetByte(0x300) == 0x60) {
		UBYTE gaps = MEMORY_dGetByte(0x30b);
		switch (cmd){
		case 0x52:	/* read */
			SIO_last_op = SIO_LAST_READ;
			SIO_last_drive = 0x61;
			SIO_last_op_time = 0x10;
			/* set expected Gap */
			CASSETTE_AddGap(gaps == 0 ? 2000 : 160);
			/* get record from storage medium */
			if (CASSETTE_ReadToMemory(data, length))
				result = 'C';
			else
				result = 'E';
			break;
		case 0x57:	/* write */
			SIO_last_op = SIO_LAST_WRITE;
			SIO_last_drive = 0x61;
			SIO_last_op_time = 0x10;
			/* add pregap length */
			CASSETTE_AddGap(gaps == 0 ? 3000 : 260);
			/* write full record to storage medium */
			if (CASSETTE_WriteFromMemory(data, length))
				result = 'C';
			else
				result = 'E';
			break;
		default:
			result = 'N';
		}
	}

	switch (result) {
	case 0x00:					/* Device disabled, generate timeout */
		CPU_regY = 138;
		CPU_SetN;
		break;
	case 'A':					/* Device acknowledge */
	case 'C':					/* Operation complete */
		CPU_regY = 1;
		CPU_ClrN;
		break;
	case 'N':					/* Device NAK */
		CPU_regY = 144;
		CPU_SetN;
		break;
	case 'E':					/* Device error */
	default:
		CPU_regY = 146;
		CPU_SetN;
		break;
	}
	CPU_regA = 0;	/* MMM */
	MEMORY_dPutByte(0x0303, CPU_regY);
	MEMORY_dPutByte(0x42,0);
	CPU_SetC;

	/* After each SIO operation a routine called SENDDS ($EC5F in OSB) is
	   invoked, which, among other functions, silences the sound
	   generators. With SIO patch we don't call SIOV and in effect SENDDS
	   is not called either, but this causes a problem with tape saving.
	   During tape saving sound generators are enabled before calling
	   SIOV, but are not disabled later (no call to SENDDS). The effect is
	   that after saving to tape the unwanted SIO sounds are left audible.
	   To avoid the problem, we silence the sound registers by hand. */
	POKEY_PutByte(POKEY_OFFSET_AUDC1, 0);
	POKEY_PutByte(POKEY_OFFSET_AUDC2, 0);
	POKEY_PutByte(POKEY_OFFSET_AUDC3, 0);
	POKEY_PutByte(POKEY_OFFSET_AUDC4, 0);
}