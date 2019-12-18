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
struct TYPE_2__ {scalar_t__ iType; int iSecondStart; int iLengthms; } ;

/* Variables and functions */
 scalar_t__ PT_VS ; 
 TYPE_1__* PhonemeData ; 
 int time_to_samples (int) ; 

int Votrax_Samples(int currentP, int nextP, int cursamples)
{
	int AdditionalSamples = 0;
	int dwCount;
	int delay = 0;
	/* some phonemes have a SecondStart */
	if ( PhonemeData[currentP].iType>=PT_VS && currentP!=nextP) {
		AdditionalSamples = PhonemeData[currentP].iSecondStart;
	}

	if ( PhonemeData[nextP].iType>=PT_VS ) {
		/* 'stop phonemes' will stop playing until the next phoneme is sent*/
		/* votraxsc01_locals.iRemainingSamples = 0; */
		return cursamples;
	}
	if (currentP == 0x3f) delay = time_to_samples(20);

	/* length of samples to produce*/
	dwCount = time_to_samples(PhonemeData[nextP].iLengthms);
	return dwCount + AdditionalSamples + delay ;
}