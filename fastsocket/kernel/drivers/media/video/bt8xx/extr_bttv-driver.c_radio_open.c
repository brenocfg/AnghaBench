#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct video_device {int dummy; } ;
struct file {struct bttv_fh* private_data; } ;
struct bttv_fh {int /*<<< orphan*/  prio; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
struct bttv {int /*<<< orphan*/  radio_user; int /*<<< orphan*/  prio; struct bttv_fh init; TYPE_1__ c; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TVAUDIO_INPUT_RADIO ; 
 int /*<<< orphan*/  audio_input (struct bttv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bttv_call_all (struct bttv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 struct bttv_fh* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_radio ; 
 int /*<<< orphan*/  tuner ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  v4l2_prio_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct video_device* video_devdata (struct file*) ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 struct bttv* video_drvdata (struct file*) ; 

__attribute__((used)) static int radio_open(struct file *file)
{
	struct video_device *vdev = video_devdata(file);
	struct bttv *btv = video_drvdata(file);
	struct bttv_fh *fh;

	dprintk("bttv: open dev=%s\n", video_device_node_name(vdev));

	dprintk("bttv%d: open called (radio)\n",btv->c.nr);

	/* allocate per filehandle data */
	fh = kmalloc(sizeof(*fh), GFP_KERNEL);
	if (unlikely(!fh))
		return -ENOMEM;
	file->private_data = fh;
	*fh = btv->init;

	v4l2_prio_open(&btv->prio, &fh->prio);

	btv->radio_user++;

	bttv_call_all(btv, tuner, s_radio);
	audio_input(btv,TVAUDIO_INPUT_RADIO);

	return 0;
}