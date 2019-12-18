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
struct channel {int tremolo_type; int tremolo_add; int tremolo_depth; int /*<<< orphan*/  tremolo_phase; } ;

/* Variables and functions */
 int channel_waveform (struct channel*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void channel_tremolo( struct channel *channel ) {
	int wave = channel_waveform( channel, channel->tremolo_phase, channel->tremolo_type & 0x3 );
	channel->tremolo_add = wave * channel->tremolo_depth >> 6;
}