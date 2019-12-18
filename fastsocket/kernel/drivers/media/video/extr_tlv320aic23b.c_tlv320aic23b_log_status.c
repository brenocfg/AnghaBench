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
struct tlv320aic23b_state {scalar_t__ muted; } ;

/* Variables and functions */
 struct tlv320aic23b_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,char*) ; 

__attribute__((used)) static int tlv320aic23b_log_status(struct v4l2_subdev *sd)
{
	struct tlv320aic23b_state *state = to_state(sd);

	v4l2_info(sd, "Input: %s\n", state->muted ? "muted" : "active");
	return 0;
}