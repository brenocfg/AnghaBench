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
struct sample {short* data; int loop_length; int loop_start; } ;
struct channel {int ampl; int pann; int sample_idx; int sample_fra; int freq; struct sample* sample; } ;

/* Variables and functions */
 int FP_MASK ; 
 int FP_SHIFT ; 

__attribute__((used)) static void channel_resample( struct channel *channel, int *mix_buf,
		int offset, int count, int sample_rate, int interpolate ) {
	struct sample *sample = channel->sample;
	int l_gain, r_gain, sam_idx, sam_fra, step;
	int loop_len, loop_end, out_idx, out_end, y, m, c;
	short *sample_data = channel->sample->data;
	if( channel->ampl > 0 ) {
		l_gain = channel->ampl * ( 255 - channel->pann ) >> 8;
		r_gain = channel->ampl * channel->pann >> 8;
		sam_idx = channel->sample_idx;
		sam_fra = channel->sample_fra;
		step = ( channel->freq << ( FP_SHIFT - 3 ) ) / ( sample_rate >> 3 );
		loop_len = sample->loop_length;
		loop_end = sample->loop_start + loop_len;
		out_idx = offset * 2;
		out_end = ( offset + count ) * 2;
		if( interpolate ) {
			while( out_idx < out_end ) {
				if( sam_idx >= loop_end ) {
					if( loop_len > 1 ) {
						while( sam_idx >= loop_end ) {
							sam_idx -= loop_len;
						}
					} else {
						break;
					}
				}
				c = sample_data[ sam_idx ];
				m = sample_data[ sam_idx + 1 ] - c;
				y = ( ( m * sam_fra ) >> FP_SHIFT ) + c;
				mix_buf[ out_idx++ ] += ( y * l_gain ) >> FP_SHIFT;
				mix_buf[ out_idx++ ] += ( y * r_gain ) >> FP_SHIFT;
				sam_fra += step;
				sam_idx += sam_fra >> FP_SHIFT;
				sam_fra &= FP_MASK;
			}
		} else {
			while( out_idx < out_end ) {
				if( sam_idx >= loop_end ) {
					if( loop_len > 1 ) {
						while( sam_idx >= loop_end ) {
							sam_idx -= loop_len;
						}
					} else {
						break;
					}
				}
				y = sample_data[ sam_idx ];
				mix_buf[ out_idx++ ] += ( y * l_gain ) >> FP_SHIFT;
				mix_buf[ out_idx++ ] += ( y * r_gain ) >> FP_SHIFT;
				sam_fra += step;
				sam_idx += sam_fra >> FP_SHIFT;
				sam_fra &= FP_MASK;
			}
		}
	}
}