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
typedef  int s32 ;

/* Variables and functions */
 void** dsp_audio_increase1 ; 
 void** dsp_audio_increase2 ; 
 void** dsp_audio_increase3 ; 
 void** dsp_audio_increase4 ; 
 void** dsp_audio_increase5 ; 
 void** dsp_audio_increase6 ; 
 void** dsp_audio_increase7 ; 
 void** dsp_audio_increase8 ; 
 int* dsp_audio_law_to_s32 ; 
 void** dsp_audio_reduce1 ; 
 void** dsp_audio_reduce2 ; 
 void** dsp_audio_reduce3 ; 
 void** dsp_audio_reduce4 ; 
 void** dsp_audio_reduce5 ; 
 void** dsp_audio_reduce6 ; 
 void** dsp_audio_reduce7 ; 
 void** dsp_audio_reduce8 ; 
 void** dsp_audio_s16_to_law ; 

void
dsp_audio_generate_volume_changes(void)
{
	register s32 sample;
	int i;
	int num[]   = { 110, 125, 150, 175, 200, 300, 400, 500 };
	int denum[] = { 100, 100, 100, 100, 100, 100, 100, 100 };

	i = 0;
	while (i < 256) {
		dsp_audio_reduce8[i] = dsp_audio_s16_to_law[
			(dsp_audio_law_to_s32[i] * denum[7] / num[7]) & 0xffff];
		dsp_audio_reduce7[i] = dsp_audio_s16_to_law[
			(dsp_audio_law_to_s32[i] * denum[6] / num[6]) & 0xffff];
		dsp_audio_reduce6[i] = dsp_audio_s16_to_law[
			(dsp_audio_law_to_s32[i] * denum[5] / num[5]) & 0xffff];
		dsp_audio_reduce5[i] = dsp_audio_s16_to_law[
			(dsp_audio_law_to_s32[i] * denum[4] / num[4]) & 0xffff];
		dsp_audio_reduce4[i] = dsp_audio_s16_to_law[
			(dsp_audio_law_to_s32[i] * denum[3] / num[3]) & 0xffff];
		dsp_audio_reduce3[i] = dsp_audio_s16_to_law[
			(dsp_audio_law_to_s32[i] * denum[2] / num[2]) & 0xffff];
		dsp_audio_reduce2[i] = dsp_audio_s16_to_law[
			(dsp_audio_law_to_s32[i] * denum[1] / num[1]) & 0xffff];
		dsp_audio_reduce1[i] = dsp_audio_s16_to_law[
			(dsp_audio_law_to_s32[i] * denum[0] / num[0]) & 0xffff];
		sample = dsp_audio_law_to_s32[i] * num[0] / denum[0];
		if (sample < -32768)
			sample = -32768;
		else if (sample > 32767)
			sample = 32767;
		dsp_audio_increase1[i] = dsp_audio_s16_to_law[sample & 0xffff];
		sample = dsp_audio_law_to_s32[i] * num[1] / denum[1];
		if (sample < -32768)
			sample = -32768;
		else if (sample > 32767)
			sample = 32767;
		dsp_audio_increase2[i] = dsp_audio_s16_to_law[sample & 0xffff];
		sample = dsp_audio_law_to_s32[i] * num[2] / denum[2];
		if (sample < -32768)
			sample = -32768;
		else if (sample > 32767)
			sample = 32767;
		dsp_audio_increase3[i] = dsp_audio_s16_to_law[sample & 0xffff];
		sample = dsp_audio_law_to_s32[i] * num[3] / denum[3];
		if (sample < -32768)
			sample = -32768;
		else if (sample > 32767)
			sample = 32767;
		dsp_audio_increase4[i] = dsp_audio_s16_to_law[sample & 0xffff];
		sample = dsp_audio_law_to_s32[i] * num[4] / denum[4];
		if (sample < -32768)
			sample = -32768;
		else if (sample > 32767)
			sample = 32767;
		dsp_audio_increase5[i] = dsp_audio_s16_to_law[sample & 0xffff];
		sample = dsp_audio_law_to_s32[i] * num[5] / denum[5];
		if (sample < -32768)
			sample = -32768;
		else if (sample > 32767)
			sample = 32767;
		dsp_audio_increase6[i] = dsp_audio_s16_to_law[sample & 0xffff];
		sample = dsp_audio_law_to_s32[i] * num[6] / denum[6];
		if (sample < -32768)
			sample = -32768;
		else if (sample > 32767)
			sample = 32767;
		dsp_audio_increase7[i] = dsp_audio_s16_to_law[sample & 0xffff];
		sample = dsp_audio_law_to_s32[i] * num[7] / denum[7];
		if (sample < -32768)
			sample = -32768;
		else if (sample > 32767)
			sample = 32767;
		dsp_audio_increase8[i] = dsp_audio_s16_to_law[sample & 0xffff];

		i++;
	}
}