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
typedef  scalar_t__ UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ClrN ; 
 int /*<<< orphan*/  CPU_SetN ; 
 scalar_t__ CPU_regA ; 
 int CPU_regY ; 
 int /*<<< orphan*/  Devices_GetIOCB () ; 
 int EOF ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ devbug ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 void* fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** h_fp ; 
 size_t h_iocb ; 
 int* h_lastbyte ; 
 char* h_lastop ; 
 scalar_t__* h_textmode ; 
 int /*<<< orphan*/ * h_wascr ; 

__attribute__((used)) static void Devices_H_Read(void)
{
	if (devbug)
		Log_print("HHREAD");
	if (!Devices_GetIOCB())
		return;
	if (h_fp[h_iocb] != NULL) {
		int ch;
		if (h_lastop[h_iocb] != 'r') {
			if (h_lastop[h_iocb] == 'w')
				fseek(h_fp[h_iocb], 0, SEEK_CUR);
			h_lastbyte[h_iocb] = fgetc(h_fp[h_iocb]);
			h_lastop[h_iocb] = 'r';
		}
		ch = h_lastbyte[h_iocb];
		if (ch != EOF) {
			if (h_textmode[h_iocb]) {
				switch (ch) {
				case 0x0d:
					h_wascr[h_iocb] = TRUE;
					ch = 0x9b;
					break;
				case 0x0a:
					if (h_wascr[h_iocb]) {
						/* ignore LF next to CR */
						ch = fgetc(h_fp[h_iocb]);
						if (ch != EOF) {
							if (ch == 0x0d) {
								h_wascr[h_iocb] = TRUE;
								ch = 0x9b;
							}
							else
								h_wascr[h_iocb] = FALSE;
						}
						else {
							CPU_regY = 136; /* end of file */
							CPU_SetN;
							break;
						}
					}
					else
						ch = 0x9b;
					break;
				default:
					h_wascr[h_iocb] = FALSE;
					break;
				}
			}
			CPU_regA = (UBYTE) ch;
			/* [OSMAN] p. 79: Status should be 3 if next read would yield EOF.
			   But to set the stream's EOF flag, we need to read the next byte. */
			h_lastbyte[h_iocb] = fgetc(h_fp[h_iocb]);
			CPU_regY = feof(h_fp[h_iocb]) ? 3 : 1;
			CPU_ClrN;
		}
		else {
			CPU_regY = 136; /* end of file */
			CPU_SetN;
		}
	}
	else {
		CPU_regY = 136; /* end of file; XXX: this seems to be what Atari DOSes return */
		CPU_SetN;
	}
}