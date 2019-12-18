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
struct channel {scalar_t__ period; scalar_t__ porta_period; int tone_porta_param; } ;

/* Variables and functions */

__attribute__((used)) static void channel_tone_porta( struct channel *channel ) {
	if( channel->period > 0 ) {
		if( channel->period < channel->porta_period ) {
			channel->period += channel->tone_porta_param << 2;
			if( channel->period > channel->porta_period ) {
				channel->period = channel->porta_period;
			}
		} else {
			channel->period -= channel->tone_porta_param << 2;
			if( channel->period < channel->porta_period ) {
				channel->period = channel->porta_period;
			}
		}
	}
}