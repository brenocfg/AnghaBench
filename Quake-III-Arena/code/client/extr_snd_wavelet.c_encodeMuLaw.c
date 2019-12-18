#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size; scalar_t__ sndChunk; struct TYPE_5__* next; } ;
typedef  TYPE_1__ sndBuffer ;
struct TYPE_6__ {int soundLength; TYPE_1__* soundData; } ;
typedef  TYPE_2__ sfx_t ;
typedef  size_t byte ;

/* Variables and functions */
 scalar_t__ MuLawDecode (size_t) ; 
 size_t MuLawEncode (short) ; 
 int SND_CHUNK_SIZE ; 
 TYPE_1__* SND_malloc () ; 
 scalar_t__ madeTable ; 
 int* mulawToShort ; 
 scalar_t__ qtrue ; 

void encodeMuLaw( sfx_t *sfx, short *packets) {
	int		i, samples, size, grade, poop;
	sndBuffer		*newchunk, *chunk;
	byte			*out;

	if (!madeTable) {
		for (i=0;i<256;i++) {
			mulawToShort[i] = (float)MuLawDecode((byte)i);
		}
		madeTable = qtrue;
	}

	chunk = NULL;
	samples = sfx->soundLength;
	grade = 0;

	while(samples>0) {
		size = samples;
		if (size>(SND_CHUNK_SIZE*2)) {
			size = (SND_CHUNK_SIZE*2);
		}

		newchunk = SND_malloc();
		if (sfx->soundData == NULL) {
			sfx->soundData = newchunk;
		} else {
			chunk->next = newchunk;
		}
		chunk = newchunk;
		out = (byte *)chunk->sndChunk;
		for(i=0; i<size; i++) {
			poop = packets[0]+grade;
			if (poop>32767) {
				poop = 32767;
			} else if (poop<-32768) {
				poop = -32768;
			}
			out[i] = MuLawEncode((short)poop);
			grade = poop - mulawToShort[out[i]];
			packets++;
		}
		chunk->size = size;
		samples -= size;
	}
}