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
struct channel {scalar_t__ retrig_count; scalar_t__ tremor_on_ticks; int tremolo_add; scalar_t__ tremor_off_ticks; } ;

/* Variables and functions */

__attribute__((used)) static void channel_tremor( struct channel *channel ) {
	if( channel->retrig_count >= channel->tremor_on_ticks ) {
		channel->tremolo_add = -64;
	}
	if( channel->retrig_count >= ( channel->tremor_on_ticks + channel->tremor_off_ticks ) ) {
		channel->tremolo_add = channel->retrig_count = 0;
	}
}