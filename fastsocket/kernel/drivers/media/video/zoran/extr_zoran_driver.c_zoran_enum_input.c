#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zoran_fh {struct zoran* zr; } ;
struct TYPE_4__ {int inputs; TYPE_1__* input; } ;
struct zoran {int /*<<< orphan*/  resource_lock; TYPE_2__ card; } ;
struct v4l2_input {int index; int /*<<< orphan*/  status; int /*<<< orphan*/  std; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_STD_ALL ; 
 int /*<<< orphan*/  decoder_call (struct zoran*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_input_status ; 
 int /*<<< orphan*/  memset (struct v4l2_input*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int zoran_enum_input(struct file *file, void *__fh,
				 struct v4l2_input *inp)
{
	struct zoran_fh *fh = __fh;
	struct zoran *zr = fh->zr;

	if (inp->index < 0 || inp->index >= zr->card.inputs)
		return -EINVAL;
	else {
		int id = inp->index;
		memset(inp, 0, sizeof(*inp));
		inp->index = id;
	}

	strncpy(inp->name, zr->card.input[inp->index].name,
		sizeof(inp->name) - 1);
	inp->type = V4L2_INPUT_TYPE_CAMERA;
	inp->std = V4L2_STD_ALL;

	/* Get status of video decoder */
	mutex_lock(&zr->resource_lock);
	decoder_call(zr, video, g_input_status, &inp->status);
	mutex_unlock(&zr->resource_lock);
	return 0;
}