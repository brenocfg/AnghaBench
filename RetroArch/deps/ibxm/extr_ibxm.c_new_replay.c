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
struct replay {int sample_rate; int interpolation; int* ramp_buf; struct channel* channels; struct module* module; } ;
struct module {int num_channels; } ;
struct channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  dispose_replay (struct replay*) ; 
 int /*<<< orphan*/  replay_set_sequence_pos (struct replay*,int /*<<< orphan*/ ) ; 

struct replay* new_replay( struct module *module, int sample_rate, int interpolation ) {
	struct replay *replay = (struct replay*)calloc( 1, sizeof( struct replay ) );
	if( replay ) {
		replay->module = module;
		replay->sample_rate = sample_rate;
		replay->interpolation = interpolation;
		replay->ramp_buf = (int*)calloc( 128, sizeof( int ) );
		replay->channels = (struct channel*)calloc( module->num_channels, sizeof( struct channel ) );
		if( replay->ramp_buf && replay->channels ) {
			replay_set_sequence_pos( replay, 0 );
		} else {
			dispose_replay( replay );
			replay = NULL;
		}
	}
	return replay;
}