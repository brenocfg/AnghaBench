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
typedef  scalar_t__ v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;
struct saa7127_state {scalar_t__ std; } ;

/* Variables and functions */
 int saa7127_set_std (struct v4l2_subdev*,scalar_t__) ; 
 struct saa7127_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int saa7127_s_std_output(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct saa7127_state *state = to_state(sd);

	if (state->std == std)
		return 0;
	return saa7127_set_std(sd, std);
}