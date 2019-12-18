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
struct channel {int period; int /*<<< orphan*/  fx_count; } ;

/* Variables and functions */

__attribute__((used)) static void channel_porta_down( struct channel *channel, int param ) {
	if( channel->period > 0 ) {
		switch( param & 0xF0 ) {
			case 0xE0: /* Extra-fine porta.*/
				if( channel->fx_count == 0 ) {
					channel->period += param & 0xF;
				}
				break;
			case 0xF0: /* Fine porta.*/
				if( channel->fx_count == 0 ) {
					channel->period += ( param & 0xF ) << 2;
				}
				break;
			default:/* Normal porta.*/
				if( channel->fx_count > 0 ) {
					channel->period += param << 2;
				}
				break;
		}
		if( channel->period > 65535 ) {
			channel->period = 65535;
		}
	}
}