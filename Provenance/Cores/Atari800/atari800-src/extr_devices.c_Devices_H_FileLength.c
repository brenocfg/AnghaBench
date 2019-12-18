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
struct stat {int st_size; } ;
typedef  int /*<<< orphan*/  UBYTE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ClrN ; 
 int CPU_regY ; 
 int /*<<< orphan*/  Devices_GetIOCB () ; 
 int /*<<< orphan*/  Devices_H_Load (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Devices_H_LoadProceed (int /*<<< orphan*/ ) ; 
 scalar_t__ Devices_ICAX3 ; 
 scalar_t__ Devices_ICAX4 ; 
 scalar_t__ Devices_ICAX5 ; 
 size_t Devices_IOCB0 ; 
 scalar_t__ EOF ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 char MEMORY_dGetByte (int) ; 
 int /*<<< orphan*/  MEMORY_dPutByte (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int Util_flen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * binf ; 
 scalar_t__ devbug ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fstat (int /*<<< orphan*/ ,struct stat*) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** h_fp ; 
 size_t h_iocb ; 
 scalar_t__* h_lastbyte ; 
 char* h_lastop ; 

__attribute__((used)) static void Devices_H_FileLength(void)
{
	if (devbug)
		Log_print("Get File Length Command");
	if (!Devices_GetIOCB())
		return;
	/* if IOCB is closed then assume it is a MyDOS Load File command */
	if (h_fp[h_iocb] == NULL)
		Devices_H_Load(TRUE);
	/* if we are running MyDOS then assume it is a MyDOS Load File command */
	else if (MEMORY_dGetByte(0x700) == 'M') {
		/* XXX: if (binf != NULL) fclose(binf); ? */

		/* In Devices_H_Read one byte is read ahead. Take it into account. */
		if (h_lastop[h_iocb] == 'r' && h_lastbyte[h_iocb] != EOF)
			fseek(h_fp[h_iocb], -1, SEEK_CUR);

		binf = h_fp[h_iocb];
		Devices_H_LoadProceed(TRUE);
		/* XXX: don't close binf when complete? */
		h_lastop[h_iocb] = 'b';
	}
	/* otherwise assume it is a file length command */
	else {
		int iocb = Devices_IOCB0 + h_iocb * 16;
		int filesize;
#if 0
		/* old, less portable implementation */
		struct stat fstatus;
		fstat(fileno(h_fp[h_iocb]), &fstatus);
		filesize = fstatus.st_size;
#else
		FILE *fp = h_fp[h_iocb];
		long currentpos = ftell(fp);
		filesize = Util_flen(fp);
		fseek(fp, currentpos, SEEK_SET);
#endif
		MEMORY_dPutByte(iocb + Devices_ICAX3, (UBYTE) filesize);
		MEMORY_dPutByte(iocb + Devices_ICAX4, (UBYTE) (filesize >> 8));
		MEMORY_dPutByte(iocb + Devices_ICAX5, (UBYTE) (filesize >> 16));
		CPU_regY = 1;
		CPU_ClrN;
	}
}