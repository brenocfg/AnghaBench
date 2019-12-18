#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int v4l2_std_id ;
struct file {struct cx231xx_fh* private_data; } ;
struct cx231xx_fh {struct cx231xx* dev; } ;
struct TYPE_6__ {int is_50hz; } ;
struct TYPE_5__ {int height; } ;
struct TYPE_7__ {int id; } ;
struct cx231xx {int /*<<< orphan*/  norm; TYPE_2__ mpeg_params; TYPE_1__ ts1; TYPE_3__ encodernorm; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_3__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_STD_NTSC ; 
 int /*<<< orphan*/  V4L2_STD_PAL_B ; 
 int /*<<< orphan*/  call_all (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  cx231xx_do_mode_ctrl_overrides (struct cx231xx*) ; 
 TYPE_3__* cx231xx_tvnorms ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  s_std ; 

__attribute__((used)) static int vidioc_s_std(struct file *file, void *priv, v4l2_std_id *id)
{
	struct cx231xx_fh  *fh  = file->private_data;
	struct cx231xx *dev = fh->dev;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(cx231xx_tvnorms); i++)
		if (*id & cx231xx_tvnorms[i].id)
			break;
	if (i == ARRAY_SIZE(cx231xx_tvnorms))
		return -EINVAL;
	dev->encodernorm = cx231xx_tvnorms[i];

	if (dev->encodernorm.id & 0xb000) {
		dprintk(3, "encodernorm set to NTSC\n");
		dev->norm = V4L2_STD_NTSC;
		dev->ts1.height = 480;
		dev->mpeg_params.is_50hz = 0;
	} else {
		dprintk(3, "encodernorm set to PAL\n");
		dev->norm = V4L2_STD_PAL_B;
		dev->ts1.height = 576;
		dev->mpeg_params.is_50hz = 1;
	}
	call_all(dev, core, s_std, dev->norm);
	/* do mode control overrides */
	cx231xx_do_mode_ctrl_overrides(dev);

	dprintk(3, "exit vidioc_s_std() i=0x%x\n", i);
	return 0;
}