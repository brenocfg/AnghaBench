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
struct saa7110 {scalar_t__ input; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SAA7110_MAX_INPUT ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  saa7110_selmux (struct v4l2_subdev*,scalar_t__) ; 
 struct saa7110* to_saa7110 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,scalar_t__) ; 

__attribute__((used)) static int saa7110_s_routing(struct v4l2_subdev *sd,
			     u32 input, u32 output, u32 config)
{
	struct saa7110 *decoder = to_saa7110(sd);

	if (input < 0 || input >= SAA7110_MAX_INPUT) {
		v4l2_dbg(1, debug, sd, "input=%d not available\n", input);
		return -EINVAL;
	}
	if (decoder->input != input) {
		saa7110_selmux(sd, input);
		v4l2_dbg(1, debug, sd, "switched to input=%d\n", input);
	}
	return 0;
}