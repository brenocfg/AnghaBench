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
struct sample {scalar_t__ loop_start; int loop_length; } ;
struct channel {int freq; int sample_fra; scalar_t__ sample_idx; struct sample* sample; } ;

/* Variables and functions */
 int FP_MASK ; 
 int FP_SHIFT ; 

__attribute__((used)) static void channel_update_sample_idx( struct channel *channel, int count, int sample_rate ) {
	struct sample *sample = channel->sample;
	int step = ( channel->freq << ( FP_SHIFT - 3 ) ) / ( sample_rate >> 3 );
	channel->sample_fra += step * count;
	channel->sample_idx += channel->sample_fra >> FP_SHIFT;
	if( channel->sample_idx > sample->loop_start ) {
		if( sample->loop_length > 1 ) {
			channel->sample_idx = sample->loop_start
				+ ( channel->sample_idx - sample->loop_start ) % sample->loop_length;
		} else {
			channel->sample_idx = sample->loop_start;
		}
	}
	channel->sample_fra &= FP_MASK;
}