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
struct v4l2_queryctrl {int type; int /*<<< orphan*/  maximum; int /*<<< orphan*/  minimum; int /*<<< orphan*/  name; } ;
struct v4l2_priv_tun_config {int /*<<< orphan*/ * priv; int /*<<< orphan*/  tuner; } ;
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct saa7134_fh {int /*<<< orphan*/  prio; } ;
struct saa7134_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  slock; int /*<<< orphan*/  tda9887_conf; int /*<<< orphan*/  ctl_automute; int /*<<< orphan*/  ctl_y_odd; int /*<<< orphan*/  ctl_y_even; int /*<<< orphan*/  ctl_mirror; int /*<<< orphan*/  ctl_saturation; int /*<<< orphan*/  ctl_invert; int /*<<< orphan*/  ctl_contrast; int /*<<< orphan*/  ctl_volume; int /*<<< orphan*/  ctl_mute; int /*<<< orphan*/  ctl_hue; int /*<<< orphan*/  ctl_bright; int /*<<< orphan*/  prio; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RESOURCE_OVERLAY ; 
 int /*<<< orphan*/  SAA7134_DEC_CHROMA_HUE ; 
 int /*<<< orphan*/  SAA7134_DEC_CHROMA_SATURATION ; 
 int /*<<< orphan*/  SAA7134_DEC_LUMA_BRIGHT ; 
 int /*<<< orphan*/  SAA7134_DEC_LUMA_CONTRAST ; 
 int /*<<< orphan*/  TDA9887_AUTOMUTE ; 
 int /*<<< orphan*/  TUNER_TDA9887 ; 
#define  V4L2_CID_AUDIO_MUTE 141 
#define  V4L2_CID_AUDIO_VOLUME 140 
#define  V4L2_CID_BRIGHTNESS 139 
#define  V4L2_CID_CONTRAST 138 
#define  V4L2_CID_HFLIP 137 
#define  V4L2_CID_HUE 136 
#define  V4L2_CID_PRIVATE_AUTOMUTE 135 
#define  V4L2_CID_PRIVATE_INVERT 134 
#define  V4L2_CID_PRIVATE_Y_EVEN 133 
#define  V4L2_CID_PRIVATE_Y_ODD 132 
#define  V4L2_CID_SATURATION 131 
#define  V4L2_CTRL_TYPE_BOOLEAN 130 
#define  V4L2_CTRL_TYPE_INTEGER 129 
#define  V4L2_CTRL_TYPE_MENU 128 
 struct v4l2_queryctrl* ctrl_by_id (int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ res_check (struct saa7134_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_config ; 
 int /*<<< orphan*/  saa7134_tvaudio_setmute (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa7134_tvaudio_setvolume (struct saa7134_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_call_all (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_priv_tun_config*) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_preview (struct saa7134_dev*,struct saa7134_fh*) ; 
 int /*<<< orphan*/  stop_preview (struct saa7134_dev*,struct saa7134_fh*) ; 
 int /*<<< orphan*/  tuner ; 
 int v4l2_prio_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int saa7134_s_ctrl_internal(struct saa7134_dev *dev,  struct saa7134_fh *fh, struct v4l2_control *c)
{
	const struct v4l2_queryctrl* ctrl;
	unsigned long flags;
	int restart_overlay = 0;
	int err;

	/* When called from the empress code fh == NULL.
	   That needs to be fixed somehow, but for now this is
	   good enough. */
	if (fh) {
		err = v4l2_prio_check(&dev->prio, fh->prio);
		if (0 != err)
			return err;
	}
	err = -EINVAL;

	mutex_lock(&dev->lock);

	ctrl = ctrl_by_id(c->id);
	if (NULL == ctrl)
		goto error;

	dprintk("set_control name=%s val=%d\n",ctrl->name,c->value);
	switch (ctrl->type) {
	case V4L2_CTRL_TYPE_BOOLEAN:
	case V4L2_CTRL_TYPE_MENU:
	case V4L2_CTRL_TYPE_INTEGER:
		if (c->value < ctrl->minimum)
			c->value = ctrl->minimum;
		if (c->value > ctrl->maximum)
			c->value = ctrl->maximum;
		break;
	default:
		/* nothing */;
	};
	switch (c->id) {
	case V4L2_CID_BRIGHTNESS:
		dev->ctl_bright = c->value;
		saa_writeb(SAA7134_DEC_LUMA_BRIGHT, dev->ctl_bright);
		break;
	case V4L2_CID_HUE:
		dev->ctl_hue = c->value;
		saa_writeb(SAA7134_DEC_CHROMA_HUE, dev->ctl_hue);
		break;
	case V4L2_CID_CONTRAST:
		dev->ctl_contrast = c->value;
		saa_writeb(SAA7134_DEC_LUMA_CONTRAST,
			   dev->ctl_invert ? -dev->ctl_contrast : dev->ctl_contrast);
		break;
	case V4L2_CID_SATURATION:
		dev->ctl_saturation = c->value;
		saa_writeb(SAA7134_DEC_CHROMA_SATURATION,
			   dev->ctl_invert ? -dev->ctl_saturation : dev->ctl_saturation);
		break;
	case V4L2_CID_AUDIO_MUTE:
		dev->ctl_mute = c->value;
		saa7134_tvaudio_setmute(dev);
		break;
	case V4L2_CID_AUDIO_VOLUME:
		dev->ctl_volume = c->value;
		saa7134_tvaudio_setvolume(dev,dev->ctl_volume);
		break;
	case V4L2_CID_PRIVATE_INVERT:
		dev->ctl_invert = c->value;
		saa_writeb(SAA7134_DEC_LUMA_CONTRAST,
			   dev->ctl_invert ? -dev->ctl_contrast : dev->ctl_contrast);
		saa_writeb(SAA7134_DEC_CHROMA_SATURATION,
			   dev->ctl_invert ? -dev->ctl_saturation : dev->ctl_saturation);
		break;
	case V4L2_CID_HFLIP:
		dev->ctl_mirror = c->value;
		restart_overlay = 1;
		break;
	case V4L2_CID_PRIVATE_Y_EVEN:
		dev->ctl_y_even = c->value;
		restart_overlay = 1;
		break;
	case V4L2_CID_PRIVATE_Y_ODD:
		dev->ctl_y_odd = c->value;
		restart_overlay = 1;
		break;
	case V4L2_CID_PRIVATE_AUTOMUTE:
	{
		struct v4l2_priv_tun_config tda9887_cfg;

		tda9887_cfg.tuner = TUNER_TDA9887;
		tda9887_cfg.priv = &dev->tda9887_conf;

		dev->ctl_automute = c->value;
		if (dev->tda9887_conf) {
			if (dev->ctl_automute)
				dev->tda9887_conf |= TDA9887_AUTOMUTE;
			else
				dev->tda9887_conf &= ~TDA9887_AUTOMUTE;

			saa_call_all(dev, tuner, s_config, &tda9887_cfg);
		}
		break;
	}
	default:
		goto error;
	}
	if (restart_overlay && fh && res_check(fh, RESOURCE_OVERLAY)) {
		spin_lock_irqsave(&dev->slock,flags);
		stop_preview(dev,fh);
		start_preview(dev,fh);
		spin_unlock_irqrestore(&dev->slock,flags);
	}
	err = 0;

error:
	mutex_unlock(&dev->lock);
	return err;
}