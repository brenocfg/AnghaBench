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
 int /*<<< orphan*/  VOICEBOX_enabled ; 
 scalar_t__ VOICEBOX_ii ; 
 int /*<<< orphan*/  VOTRAXSND_PutByte (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

void VOICEBOX_SKCTLPutByte(int byte)
{
	static int prev_byte;
	static int prev_prev_byte;
	static int voice_box_byte;
	static int voice_box_bit;
	if (!VOICEBOX_enabled || VOICEBOX_ii) return;
	if (PIA_PACTL&0x08) return; /* Cassette motor line must be on */
#ifdef DEBUG_VOICEBOX
	printf ("SKCTL: %2x\n",byte);
#endif
	if (prev_prev_byte == 0xf7 && prev_byte == 0x03 && (byte == 0xff || byte == 0x03)) {
		if (byte != 0x03) {
			voice_box_byte += (1<< (7-voice_box_bit));
		}
		voice_box_bit++;
		if (voice_box_bit > 7 ) {
			voice_box_bit = 0;
#ifdef DEBUG_VOICEBOX
			printf("VOICE BOX BYTE: %02X\n",voice_box_byte);
#endif
			VOTRAXSND_PutByte(voice_box_byte);
			voice_box_byte = 0;
		}
	}
	prev_prev_byte = prev_byte;
	prev_byte = byte;
}