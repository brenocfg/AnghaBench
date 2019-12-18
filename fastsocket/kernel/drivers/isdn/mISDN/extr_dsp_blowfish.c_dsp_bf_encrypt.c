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
typedef  size_t u8 ;
typedef  int u32 ;
struct dsp {int bf_crypt_pos; size_t* bf_data_in; size_t* bf_crypt_out; int* bf_p; int* bf_s; } ;

/* Variables and functions */
 int /*<<< orphan*/  EROUND (int,int,int) ; 
 int* dsp_audio_law2seven ; 

void
dsp_bf_encrypt(struct dsp *dsp, u8 *data, int len)
{
	int i = 0, j = dsp->bf_crypt_pos;
	u8 *bf_data_in = dsp->bf_data_in;
	u8 *bf_crypt_out = dsp->bf_crypt_out;
	u32 *P = dsp->bf_p;
	u32 *S = dsp->bf_s;
	u32 yl, yr;
	u32 cs;
	u8 nibble;

	while (i < len) {
		/* collect a block of 9 samples */
		if (j < 9) {
			bf_data_in[j] = *data;
			*data++ = bf_crypt_out[j++];
			i++;
			continue;
		}
		j = 0;
		/* transcode 9 samples xlaw to 8 bytes */
		yl = dsp_audio_law2seven[bf_data_in[0]];
		yl = (yl<<7) | dsp_audio_law2seven[bf_data_in[1]];
		yl = (yl<<7) | dsp_audio_law2seven[bf_data_in[2]];
		yl = (yl<<7) | dsp_audio_law2seven[bf_data_in[3]];
		nibble = dsp_audio_law2seven[bf_data_in[4]];
		yr = nibble;
		yl = (yl<<4) | (nibble>>3);
		yr = (yr<<7) | dsp_audio_law2seven[bf_data_in[5]];
		yr = (yr<<7) | dsp_audio_law2seven[bf_data_in[6]];
		yr = (yr<<7) | dsp_audio_law2seven[bf_data_in[7]];
		yr = (yr<<7) | dsp_audio_law2seven[bf_data_in[8]];
		yr = (yr<<1) | (bf_data_in[0] & 1);

		/* fill unused bit with random noise of audio input */
		/* encrypt */

		EROUND(yr, yl, 0);
		EROUND(yl, yr, 1);
		EROUND(yr, yl, 2);
		EROUND(yl, yr, 3);
		EROUND(yr, yl, 4);
		EROUND(yl, yr, 5);
		EROUND(yr, yl, 6);
		EROUND(yl, yr, 7);
		EROUND(yr, yl, 8);
		EROUND(yl, yr, 9);
		EROUND(yr, yl, 10);
		EROUND(yl, yr, 11);
		EROUND(yr, yl, 12);
		EROUND(yl, yr, 13);
		EROUND(yr, yl, 14);
		EROUND(yl, yr, 15);
		yl ^= P[16];
		yr ^= P[17];

		/* calculate 3-bit checksumme */
		cs = yl ^ (yl>>3) ^ (yl>>6) ^ (yl>>9) ^ (yl>>12) ^ (yl>>15)
			^ (yl>>18) ^ (yl>>21) ^ (yl>>24) ^ (yl>>27) ^ (yl>>30)
			^ (yr<<2) ^ (yr>>1) ^ (yr>>4) ^ (yr>>7) ^ (yr>>10)
			^ (yr>>13) ^ (yr>>16) ^ (yr>>19) ^ (yr>>22) ^ (yr>>25)
			^ (yr>>28) ^ (yr>>31);

		/*
		 * transcode 8 crypted bytes to 9 data bytes with sync
		 * and checksum information
		 */
		bf_crypt_out[0] = (yl>>25) | 0x80;
		bf_crypt_out[1] = (yl>>18) & 0x7f;
		bf_crypt_out[2] = (yl>>11) & 0x7f;
		bf_crypt_out[3] = (yl>>4) & 0x7f;
		bf_crypt_out[4] = ((yl<<3) & 0x78) | ((yr>>29) & 0x07);
		bf_crypt_out[5] = ((yr>>22) & 0x7f) | ((cs<<5) & 0x80);
		bf_crypt_out[6] = ((yr>>15) & 0x7f) | ((cs<<6) & 0x80);
		bf_crypt_out[7] = ((yr>>8) & 0x7f) | (cs<<7);
		bf_crypt_out[8] = yr;
	}

	/* write current count */
	dsp->bf_crypt_pos = j;

}