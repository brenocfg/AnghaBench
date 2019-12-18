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
struct channel {int random_seed; } ;

/* Variables and functions */
 int* sine_table ; 

__attribute__((used)) static int channel_waveform( struct channel *channel, int phase, int type ) {
	int amplitude = 0;
	switch( type ) {
		default: /* Sine. */
			amplitude = sine_table[ phase & 0x1F ];
			if( ( phase & 0x20 ) > 0 ) {
				amplitude = -amplitude;
			}
			break;
		case 6: /* Saw Up.*/
			amplitude = ( ( ( phase + 0x20 ) & 0x3F ) << 3 ) - 255;
			break;
		case 1: case 7: /* Saw Down. */
			amplitude = 255 - ( ( ( phase + 0x20 ) & 0x3F ) << 3 );
			break;
		case 2: case 5: /* Square. */
			amplitude = ( phase & 0x20 ) > 0 ? 255 : -255;
			break;
		case 3: case 8: /* Random. */
			amplitude = ( channel->random_seed >> 20 ) - 255;
			channel->random_seed = ( channel->random_seed * 65 + 17 ) & 0x1FFFFFFF;
			break;
	}
	return amplitude;
}