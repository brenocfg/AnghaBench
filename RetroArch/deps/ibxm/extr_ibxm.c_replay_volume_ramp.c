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
struct replay {int sample_rate; int* ramp_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static void replay_volume_ramp( struct replay *replay, int *mix_buf, int tick_len ) {
	int idx, a1, a2, ramp_rate = 256 * 2048 / replay->sample_rate;
	for( idx = 0, a1 = 0; a1 < 256; idx += 2, a1 += ramp_rate ) {
		a2 = 256 - a1;
		mix_buf[ idx     ] = ( mix_buf[ idx     ] * a1 + replay->ramp_buf[ idx     ] * a2 ) >> 8;
		mix_buf[ idx + 1 ] = ( mix_buf[ idx + 1 ] * a1 + replay->ramp_buf[ idx + 1 ] * a2 ) >> 8;
	}
	memcpy( replay->ramp_buf, &mix_buf[ tick_len * 2 ], 128 * sizeof( int ) );
}