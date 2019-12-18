#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float samples; scalar_t__ rate; } ;
typedef  TYPE_1__ wavinfo_t ;
typedef  int /*<<< orphan*/  adpcm_state_t ;
struct TYPE_5__ {float speed; } ;

/* Variables and functions */
 int PAINTBUFFER_SIZE ; 
 TYPE_2__ dma ; 

int S_AdpcmMemoryNeeded( const wavinfo_t *info ) {
	float	scale;
	int		scaledSampleCount;
	int		sampleMemory;
	int		blockCount;
	int		headerMemory;

	// determine scale to convert from input sampling rate to desired sampling rate
	scale = (float)info->rate / dma.speed;

	// calc number of samples at playback sampling rate
	scaledSampleCount = info->samples / scale;

	// calc memory need to store those samples using ADPCM at 4 bits per sample
	sampleMemory = scaledSampleCount / 2;

	// calc number of sample blocks needed of PAINTBUFFER_SIZE
	blockCount = scaledSampleCount / PAINTBUFFER_SIZE;
	if( scaledSampleCount % PAINTBUFFER_SIZE ) {
		blockCount++;
	}

	// calc memory needed to store the block headers
	headerMemory = blockCount * sizeof(adpcm_state_t);

	return sampleMemory + headerMemory;
}