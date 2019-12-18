#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ iType; int iSecondStart; int iLengthms; int** lpStart; scalar_t__ sameAs; int* iLength; } ;
struct TYPE_3__ {size_t actPhoneme; int iRemainingSamples; int iSamplesInBuffer; int* lpBuffer; size_t actIntonation; int* pActPos; int* pBufferPos; int /*<<< orphan*/  iDelay; } ;
typedef  int SWORD ;

/* Variables and functions */
#define  PT_F 134 
#define  PT_FS 133 
#define  PT_N 132 
#define  PT_NS 131 
#define  PT_V 130 
#define  PT_VF 129 
#define  PT_VS 128 
 TYPE_2__* PhonemeData ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 double sin (double) ; 
 int time_to_samples (int) ; 
 TYPE_1__ votraxsc01_locals ; 

__attribute__((used)) static void PrepareVoiceData(int nextPhoneme, int nextIntonation)
{
	int iNextRemainingSamples;
	SWORD *pNextPos, *lpHelp;

	int iFadeOutSamples;
	int iFadeOutPos;
	
	int iFadeInSamples;
	int iFadeInPos;

	int doMix;
	/* used only for SecondStart phonemes */
	int AdditionalSamples;
	/* dwCount is the length of samples to produce in ms from iLengthms */
	int dwCount, i;

	SWORD data;

	AdditionalSamples = 0;
	/* some phonenemes have a SecondStart */
	if ( PhonemeData[votraxsc01_locals.actPhoneme].iType>=PT_VS && votraxsc01_locals.actPhoneme!=nextPhoneme ) {
		AdditionalSamples = PhonemeData[votraxsc01_locals.actPhoneme].iSecondStart;
	}

	if ( PhonemeData[nextPhoneme].iType>=PT_VS ) {
		/* 'stop phonemes' will stop playing until the next phoneme is sent*/
		votraxsc01_locals.iRemainingSamples = 0;
		return;
	}

	/* length of samples to produce*/
	dwCount = time_to_samples(PhonemeData[nextPhoneme].iLengthms);

	votraxsc01_locals.iSamplesInBuffer = dwCount+AdditionalSamples;

	if ( AdditionalSamples )
		memcpy(votraxsc01_locals.lpBuffer, PhonemeData[votraxsc01_locals.actPhoneme].lpStart[votraxsc01_locals.actIntonation], AdditionalSamples*sizeof(SWORD));

	lpHelp = votraxsc01_locals.lpBuffer + AdditionalSamples;

	iNextRemainingSamples = 0;
	pNextPos = NULL;

	iFadeOutSamples = 0;
	iFadeOutPos     = 0;
	
	iFadeInSamples   = 0;
	iFadeInPos       = 0;

	doMix = 0;

	/* set up processing*/
	if ( PhonemeData[votraxsc01_locals.actPhoneme].sameAs!=PhonemeData[nextPhoneme].sameAs  ) {
		/* do something, if they are the same all FadeIn/Out values are 0, */
		/* the buffer is simply filled with the samples of the new phoneme */

		switch ( PhonemeData[votraxsc01_locals.actPhoneme].iType ) {
			case PT_NS:
				/* "fade" out NS:*/
				iFadeOutSamples = time_to_samples(30);
				iFadeOutPos = 0;

				/* fade in new phoneme*/
				iFadeInPos = -time_to_samples(30);
				iFadeInSamples = time_to_samples(30);
				break;

			case PT_V:
			case PT_VF:
				switch ( PhonemeData[nextPhoneme].iType ){
					case PT_F:
					case PT_VF:
						/* V-->F, V-->VF: fade out 30 ms fade in from 30 ms to 60 ms without mixing*/
						iFadeOutPos = 0;
						iFadeOutSamples = time_to_samples(30);

						iFadeInPos = -time_to_samples(30);
						iFadeInSamples = time_to_samples(30);
						break;

					case PT_N:
						/* V-->N: fade out 40 ms fade from 0 ms to 40 ms without mixing*/
						iFadeOutPos = 0;
						iFadeOutSamples = time_to_samples(40);

						iFadeInPos = -time_to_samples(10);
						iFadeInSamples = time_to_samples(10);
						break;

					default:
						/* fade out 20 ms, no fade in from 10 ms to 30 ms*/
						iFadeOutPos = 0;
						iFadeOutSamples = time_to_samples(20);

						iFadeInPos = -time_to_samples(0);
						iFadeInSamples = time_to_samples(20);
						break;
				}
				break;

			case PT_N:
				switch ( PhonemeData[nextPhoneme].iType ){
					case PT_V:
					case PT_VF:
						/* N-->V, N-->VF: fade out 30 ms fade in from 10 ms to 50 ms without mixing*/
						iFadeOutPos = 0;
						iFadeOutSamples = time_to_samples(30);

						iFadeInPos = -time_to_samples(10);
						iFadeInSamples = time_to_samples(40);
						break;

					default:
						break;
				}

			case PT_VS:
			case PT_FS:
				iFadeOutPos = 0;
				iFadeOutSamples = PhonemeData[votraxsc01_locals.actPhoneme].iLength[votraxsc01_locals.actIntonation] - PhonemeData[votraxsc01_locals.actPhoneme].iSecondStart;
				votraxsc01_locals.pActPos = PhonemeData[votraxsc01_locals.actPhoneme].lpStart[votraxsc01_locals.actIntonation] + PhonemeData[votraxsc01_locals.actPhoneme].iSecondStart;
				votraxsc01_locals.iRemainingSamples = iFadeOutSamples;
				doMix = 1;

				iFadeInPos = -time_to_samples(0);
				iFadeInSamples = time_to_samples(0);

				break;

			default:
				/* fade out 30 ms, no fade in*/
				iFadeOutPos = 0;
				iFadeOutSamples = time_to_samples(20);

				iFadeInPos = -time_to_samples(20);
				break;
		}

		if ( !votraxsc01_locals.iDelay ) {
			/* this is true if after a stop and a phoneme was sent a second phoneme is sent*/
			/* during the delay time of the chip. Ignore the first phoneme data*/
			iFadeOutPos = 0;
			iFadeOutSamples = 0;
		}

	}
	else {
		/* the next one is of the same type as the previous one; continue to use the samples of the last phoneme*/
		iNextRemainingSamples = votraxsc01_locals.iRemainingSamples;
		pNextPos = votraxsc01_locals.pActPos;
	}

	for (i=0; i<dwCount; i++)
	{
		data = 0x00;

		/* fade out*/
		if ( iFadeOutPos<iFadeOutSamples ) 
		{
			double dFadeOut = 1.0;

			if ( !doMix )
				dFadeOut = 1.0-sin((1.0*iFadeOutPos/iFadeOutSamples)*3.1415/2);

			if ( !votraxsc01_locals.iRemainingSamples ) {
				votraxsc01_locals.iRemainingSamples = PhonemeData[votraxsc01_locals.actPhoneme].iLength[votraxsc01_locals.actIntonation];
				votraxsc01_locals.pActPos = PhonemeData[votraxsc01_locals.actPhoneme].lpStart[votraxsc01_locals.actIntonation];
			}

			data = (SWORD) (*votraxsc01_locals.pActPos++ * dFadeOut);

			votraxsc01_locals.iRemainingSamples--;
			iFadeOutPos++;
		}

		/* fade in or copy*/
		if ( iFadeInPos>=0 )
		{
			double dFadeIn = 1.0;
			
			if ( iFadeInPos<iFadeInSamples ) {
				dFadeIn = sin((1.0*iFadeInPos/iFadeInSamples)*3.1415/2);
				iFadeInPos++;
			}

			if ( !iNextRemainingSamples ) {
				iNextRemainingSamples = PhonemeData[nextPhoneme].iLength[nextIntonation];
				pNextPos = PhonemeData[nextPhoneme].lpStart[nextIntonation];
			}

			data += (SWORD) (*pNextPos++ * dFadeIn);
			
			iNextRemainingSamples--;
		}
		iFadeInPos++;

		*lpHelp++ = data;
	}

	votraxsc01_locals.pBufferPos = votraxsc01_locals.lpBuffer;

	votraxsc01_locals.pActPos = pNextPos;
	votraxsc01_locals.iRemainingSamples = iNextRemainingSamples;
}