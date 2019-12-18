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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {scalar_t__ startSample; TYPE_1__* thesfx; } ;
typedef  TYPE_2__ channel_t ;
struct TYPE_5__ {scalar_t__ soundLength; } ;

/* Variables and functions */
 int MAX_CHANNELS ; 
 scalar_t__ START_SAMPLE_IMMEDIATE ; 
 int /*<<< orphan*/  S_ChannelFree (TYPE_2__*) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_2__* s_channels ; 
 scalar_t__ s_paintedtime ; 

qboolean S_ScanChannelStarts( void ) {
	channel_t		*ch;
	int				i;
	qboolean		newSamples;

	newSamples = qfalse;
	ch = s_channels;

	for (i=0; i<MAX_CHANNELS ; i++, ch++) {
		if ( !ch->thesfx ) {
			continue;
		}
		// if this channel was just started this frame,
		// set the sample count to it begins mixing
		// into the very first sample
		if ( ch->startSample == START_SAMPLE_IMMEDIATE ) {
			ch->startSample = s_paintedtime;
			newSamples = qtrue;
			continue;
		}

		// if it is completely finished by now, clear it
		if ( ch->startSample + (ch->thesfx->soundLength) <= s_paintedtime ) {
			S_ChannelFree(ch);
		}
	}

	return newSamples;
}