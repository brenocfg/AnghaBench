#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;
struct tvp514x_decoder {int num_stds; int current_std; TYPE_3__* std_list; TYPE_1__* tvp514x_regs; } ;
struct TYPE_5__ {int id; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_2__ standard; int /*<<< orphan*/  video_std; } ;
struct TYPE_4__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t REG_VIDEO_STD ; 
 int STD_INVALID ; 
 int /*<<< orphan*/  debug ; 
 struct tvp514x_decoder* to_decoder (struct v4l2_subdev*) ; 
 int tvp514x_write_reg (struct v4l2_subdev*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tvp514x_s_std(struct v4l2_subdev *sd, v4l2_std_id std_id)
{
	struct tvp514x_decoder *decoder = to_decoder(sd);
	int err, i;

	for (i = 0; i < decoder->num_stds; i++)
		if (std_id & decoder->std_list[i].standard.id)
			break;

	if ((i == decoder->num_stds) || (i == STD_INVALID))
		return -EINVAL;

	err = tvp514x_write_reg(sd, REG_VIDEO_STD,
				decoder->std_list[i].video_std);
	if (err)
		return err;

	decoder->current_std = i;
	decoder->tvp514x_regs[REG_VIDEO_STD].val =
		decoder->std_list[i].video_std;

	v4l2_dbg(1, debug, sd, "Standard set to: %s",
			decoder->std_list[i].standard.name);
	return 0;
}