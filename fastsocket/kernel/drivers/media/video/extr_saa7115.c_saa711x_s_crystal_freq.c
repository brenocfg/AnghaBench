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
typedef  scalar_t__ u32 ;
struct v4l2_subdev {int dummy; } ;
struct saa711x_state {int cgcdiv; int ucgc; int apll; int /*<<< orphan*/  audclk_freq; scalar_t__ crystal_freq; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SAA7115_FREQ_24_576_MHZ ; 
 scalar_t__ SAA7115_FREQ_32_11_MHZ ; 
 scalar_t__ SAA7115_FREQ_FL_APLL ; 
 scalar_t__ SAA7115_FREQ_FL_CGCDIV ; 
 scalar_t__ SAA7115_FREQ_FL_UCGC ; 
 int /*<<< orphan*/  saa711x_s_clock_freq (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct saa711x_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int saa711x_s_crystal_freq(struct v4l2_subdev *sd, u32 freq, u32 flags)
{
	struct saa711x_state *state = to_state(sd);

	if (freq != SAA7115_FREQ_32_11_MHZ && freq != SAA7115_FREQ_24_576_MHZ)
		return -EINVAL;
	state->crystal_freq = freq;
	state->cgcdiv = (flags & SAA7115_FREQ_FL_CGCDIV) ? 3 : 4;
	state->ucgc = (flags & SAA7115_FREQ_FL_UCGC) ? 1 : 0;
	state->apll = (flags & SAA7115_FREQ_FL_APLL) ? 1 : 0;
	saa711x_s_clock_freq(sd, state->audclk_freq);
	return 0;
}