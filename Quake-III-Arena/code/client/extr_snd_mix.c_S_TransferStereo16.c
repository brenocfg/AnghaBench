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
struct TYPE_2__ {int samples; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_WriteLinearBlastStereo16 () ; 
 TYPE_1__ dma ; 
 scalar_t__ paintbuffer ; 
 int s_paintedtime ; 
 int snd_linear_count ; 
 short* snd_out ; 
 int* snd_p ; 

void S_TransferStereo16 (unsigned long *pbuf, int endtime)
{
	int		lpos;
	int		ls_paintedtime;
	
	snd_p = (int *) paintbuffer;
	ls_paintedtime = s_paintedtime;

	while (ls_paintedtime < endtime)
	{
	// handle recirculating buffer issues
		lpos = ls_paintedtime & ((dma.samples>>1)-1);

		snd_out = (short *) pbuf + (lpos<<1);

		snd_linear_count = (dma.samples>>1) - lpos;
		if (ls_paintedtime + snd_linear_count > endtime)
			snd_linear_count = endtime - ls_paintedtime;

		snd_linear_count <<= 1;

	// write a linear blast of samples
		S_WriteLinearBlastStereo16 ();

		snd_p += snd_linear_count;
		ls_paintedtime += (snd_linear_count>>1);
	}
}