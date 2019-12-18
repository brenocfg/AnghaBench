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
typedef  int u32 ;
typedef  int s32 ;
typedef  int s16 ;

/* Variables and functions */
 int AO_FAIL ; 
 int AO_SUCCESS ; 
 int /*<<< orphan*/  M68KExec (int) ; 
 int /*<<< orphan*/  ScspConvert32uto16s (int*,int*,int*,int) ; 
 scalar_t__ decaybegin ; 
 scalar_t__ decayend ; 
 int /*<<< orphan*/  scsp_update (int*,int*,int) ; 
 int /*<<< orphan*/  scsp_update_monitor () ; 
 int /*<<< orphan*/  scsp_update_timer (int) ; 
 scalar_t__ total_samples ; 

s32 ssf_gen(s16 *buffer, u32 samples)
{
	int i;
	s16 output[44100/30], output2[44100/30];
	//s16 *stereo[2];
	s16 *outp = buffer;
	int opos;

	opos = 0;
	for (i = 0; i < samples; i++)
	{
		s32 bufL=0, bufR=0;
		s16 buf16[2];
		M68KExec((11300000/60)/735);
		scsp_update_timer(1);
		scsp_update(&bufL, &bufR, 1);
		scsp_update_monitor();
		ScspConvert32uto16s (&bufL, &bufR, buf16, 1);
		output[opos] = buf16[0];
		output2[opos] = buf16[1];
		opos++;
	}

	for (i = 0; i < samples; i++)
	{
		// process the fade tags
		if (total_samples >= decaybegin)
		{
			if (total_samples >= decayend)
			{
				// song is done here, call out as necessary to make your player stop
				output[i] = 0;
				output2[i] = 0;
				return AO_FAIL;
			}
			else
			{
				s32 fader = 256 - (256*(total_samples - decaybegin)/(decayend-decaybegin));
				output[i] = (output[i] * fader)>>8;
				output2[i] = (output2[i] * fader)>>8;

				total_samples++;
			}
		}
		else
		{
			total_samples++;
		}

		*outp++ = output[i];
		*outp++ = output2[i];
	}

	return AO_SUCCESS;
}