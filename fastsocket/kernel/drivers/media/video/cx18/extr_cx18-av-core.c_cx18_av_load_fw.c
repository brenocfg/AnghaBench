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
struct v4l2_subdev {int dummy; } ;
struct cx18_av_state {int is_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx18_av_initialize (struct v4l2_subdev*) ; 
 struct cx18_av_state* to_cx18_av_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int cx18_av_load_fw(struct v4l2_subdev *sd)
{
	struct cx18_av_state *state = to_cx18_av_state(sd);

	if (!state->is_initialized) {
		/* initialize on first use */
		state->is_initialized = 1;
		cx18_av_initialize(sd);
	}
	return 0;
}