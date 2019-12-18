#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ iType; int* lpStart; int* iLength; } ;
struct TYPE_5__ {int actIntonation; int iDelay; int iSamplesInBuffer; int iRemainingSamples; size_t actPhoneme; int pActPos; int pBufferPos; scalar_t__ busy; TYPE_1__* intf; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* BusyCallback ) (scalar_t__) ;} ;
typedef  int /*<<< orphan*/  SWORD ;

/* Variables and functions */
 scalar_t__ PT_VS ; 
 TYPE_3__* PhonemeData ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 TYPE_2__ votraxsc01_locals ; 

void Votrax_Update(int num, SWORD *buffer, int length)
{
	int samplesToCopy;

#if 0
	/* if it is a different intonation */
	if ( num!=votraxsc01_locals.actIntonation ) {
		/* clear buffer */
		memset(buffer, 0x00, length*sizeof(SWORD));
		return;
	}
#endif

	while ( length ) {
		/* Case 1: if in a delay state, output 0's*/
		if ( votraxsc01_locals.iDelay ) {
			samplesToCopy = (length<=votraxsc01_locals.iDelay)?length:votraxsc01_locals.iDelay;

			memset(buffer, 0x00, samplesToCopy*sizeof(SWORD));
			buffer += samplesToCopy;

			votraxsc01_locals.iDelay -= samplesToCopy;
			length -= samplesToCopy; /* missing in the original */
		}
		/* Case 2: there are no samples left in the buffer */
		else if ( votraxsc01_locals.iSamplesInBuffer==0 ) {
			if ( votraxsc01_locals.busy ) {
				/* busy -> idle */
				votraxsc01_locals.busy = 0;
				if ( votraxsc01_locals.intf->BusyCallback )
					(*votraxsc01_locals.intf->BusyCallback)(votraxsc01_locals.busy);
			}

			if ( votraxsc01_locals.iRemainingSamples==0 ) {
				if ( PhonemeData[votraxsc01_locals.actPhoneme].iType>=PT_VS ) {
					votraxsc01_locals.pActPos = PhonemeData[0x3f].lpStart[0];
					votraxsc01_locals.iRemainingSamples = PhonemeData[0x3f].iLength[0];
				}
				else {
					votraxsc01_locals.pActPos = PhonemeData[votraxsc01_locals.actPhoneme].lpStart[votraxsc01_locals.actIntonation];
					votraxsc01_locals.iRemainingSamples = PhonemeData[votraxsc01_locals.actPhoneme].iLength[votraxsc01_locals.actIntonation];
				}

			}

			/* if there aren't enough remaining, reduce the amount */
			samplesToCopy = (length<=votraxsc01_locals.iRemainingSamples)?length:votraxsc01_locals.iRemainingSamples;

			memcpy(buffer, votraxsc01_locals.pActPos, samplesToCopy*sizeof(SWORD));
			buffer += samplesToCopy;

			votraxsc01_locals.pActPos += samplesToCopy;
			votraxsc01_locals.iRemainingSamples -= samplesToCopy;

			length -= samplesToCopy;
		}
		/* Case 3: output the samples in the buffer */
		else {
			samplesToCopy = (length<=votraxsc01_locals.iSamplesInBuffer)?length:votraxsc01_locals.iSamplesInBuffer;

			memcpy(buffer, votraxsc01_locals.pBufferPos, samplesToCopy*sizeof(SWORD));
			buffer += samplesToCopy;

			votraxsc01_locals.pBufferPos += samplesToCopy;
			votraxsc01_locals.iSamplesInBuffer -= samplesToCopy;

			length -= samplesToCopy;
		}
	}
}