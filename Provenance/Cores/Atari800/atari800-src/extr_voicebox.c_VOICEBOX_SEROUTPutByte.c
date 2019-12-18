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
 int PIA_PACTL ; 
 int* POKEY_AUDCTL ; 
 int* POKEY_AUDF ; 
 int POKEY_SKCTL ; 
 int /*<<< orphan*/  VOICEBOX_enabled ; 
 int /*<<< orphan*/  VOICEBOX_ii ; 
 int /*<<< orphan*/  VOTRAXSND_PutByte (int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int) ; 

void VOICEBOX_SEROUTPutByte(int byte)
{
	if (!VOICEBOX_enabled || !VOICEBOX_ii) return;
	if (PIA_PACTL&0x08) return; /* Cassette motor line must be on */
	if ((POKEY_SKCTL & 0x70) == 0x60 ) {
		int byte_swapped = 0;
		int i;
		for (i=0;i<8;i++) {
			byte_swapped += ((!!(byte&(1<<i)))<<(7-i));
		}
#ifdef DEBUG_VOICEBOX
		printf("VOICEBOX: %02x audf:%02X %02X %02X %02X, AUDCTL:%02X\n",byte_swapped,POKEY_AUDF[0],POKEY_AUDF[1],POKEY_AUDF[2],POKEY_AUDF[3],POKEY_AUDCTL[0]);
#endif
		VOTRAXSND_PutByte(byte_swapped);
	}
}