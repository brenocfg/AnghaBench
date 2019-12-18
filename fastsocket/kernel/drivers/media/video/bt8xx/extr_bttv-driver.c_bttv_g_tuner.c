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
struct v4l2_tuner {scalar_t__ index; int signal; int /*<<< orphan*/  type; int /*<<< orphan*/  capability; int /*<<< orphan*/  name; int /*<<< orphan*/  rxsubchans; } ;
struct file {int dummy; } ;
struct bttv_fh {struct bttv* btv; } ;
struct bttv {scalar_t__ tuner_type; int /*<<< orphan*/  (* audio_mode_gpio ) (struct bttv*,struct v4l2_tuner*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_DSTATUS ; 
 int BT848_DSTATUS_HLOC ; 
 int EINVAL ; 
 scalar_t__ TUNER_ABSENT ; 
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int /*<<< orphan*/  V4L2_TUNER_CAP_NORM ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_MONO ; 
 int btread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bttv_call_all (struct bttv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_tuner*) ; 
 int /*<<< orphan*/  g_tuner ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct bttv*,struct v4l2_tuner*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuner ; 

__attribute__((used)) static int bttv_g_tuner(struct file *file, void *priv,
				struct v4l2_tuner *t)
{
	struct bttv_fh *fh = priv;
	struct bttv *btv = fh->btv;

	if (btv->tuner_type == TUNER_ABSENT)
		return -EINVAL;
	if (0 != t->index)
		return -EINVAL;

	t->rxsubchans = V4L2_TUNER_SUB_MONO;
	bttv_call_all(btv, tuner, g_tuner, t);
	strcpy(t->name, "Television");
	t->capability = V4L2_TUNER_CAP_NORM;
	t->type       = V4L2_TUNER_ANALOG_TV;
	if (btread(BT848_DSTATUS)&BT848_DSTATUS_HLOC)
		t->signal = 0xffff;

	if (btv->audio_mode_gpio)
		btv->audio_mode_gpio(btv, t, 0);

	return 0;
}