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
struct channel {int vibrato_type; int vibrato_add; int vibrato_depth; int /*<<< orphan*/  vibrato_phase; } ;

/* Variables and functions */
 int channel_waveform (struct channel*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void channel_vibrato( struct channel *channel, int fine ) {
	int wave = channel_waveform( channel, channel->vibrato_phase, channel->vibrato_type & 0x3 );
	channel->vibrato_add = wave * channel->vibrato_depth >> ( fine ? 7 : 5 );
}