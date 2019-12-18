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
typedef  int u32 ;
struct v4l2_frequency {int frequency; scalar_t__ type; scalar_t__ tuner; } ;
struct file {int dummy; } ;
struct cx231xx_fh {int radio; struct cx231xx* dev; } ;
struct cx231xx {int ctl_freq; scalar_t__ tuner_type; int norm; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TUNER_NXP_TDA18271 ; 
 int V4L2_STD_B ; 
 int V4L2_STD_GH ; 
 int V4L2_STD_MN ; 
 int V4L2_STD_NTSC_443 ; 
 int V4L2_STD_PAL_DK ; 
 int V4L2_STD_PAL_I ; 
 int V4L2_STD_SECAM_DK ; 
 int V4L2_STD_SECAM_L ; 
 int V4L2_STD_SECAM_LC ; 
 scalar_t__ V4L2_TUNER_ANALOG_TV ; 
 scalar_t__ V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  call_all (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 
 int check_dev (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_info (char*,int,...) ; 
 int /*<<< orphan*/  cx231xx_set_Colibri_For_LowIF (struct cx231xx*,int,int,int) ; 
 int cx231xx_tuner_post_channel_change (struct cx231xx*) ; 
 int cx231xx_tuner_pre_channel_change (struct cx231xx*) ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  tuner ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_HH_register_after_set_DIF (struct cx231xx*) ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *priv,
			      struct v4l2_frequency *f)
{
	struct cx231xx_fh *fh = priv;
	struct cx231xx *dev = fh->dev;
	int rc;
	u32 if_frequency = 5400000;

	cx231xx_info("Enter vidioc_s_frequency()f->frequency=%d;f->type=%d\n",
		 f->frequency, f->type);
	/*cx231xx_info("f->type:  1-radio 2-analogTV 3-digitalTV\n");*/

	rc = check_dev(dev);
	if (rc < 0)
		return rc;

	if (0 != f->tuner)
		return -EINVAL;

	if (unlikely(0 == fh->radio && f->type != V4L2_TUNER_ANALOG_TV))
		return -EINVAL;
	if (unlikely(1 == fh->radio && f->type != V4L2_TUNER_RADIO))
		return -EINVAL;

	/* set pre channel change settings in DIF first */
	rc = cx231xx_tuner_pre_channel_change(dev);

	dev->ctl_freq = f->frequency;
	call_all(dev, tuner, s_frequency, f);

	/* set post channel change settings in DIF first */
	rc = cx231xx_tuner_post_channel_change(dev);

	if (dev->tuner_type == TUNER_NXP_TDA18271) {
		if (dev->norm & (V4L2_STD_MN | V4L2_STD_NTSC_443))
			if_frequency = 5400000;  /*5.4MHz	*/
		else if (dev->norm & V4L2_STD_B)
			if_frequency = 6000000;  /*6.0MHz	*/
		else if (dev->norm & (V4L2_STD_PAL_DK | V4L2_STD_SECAM_DK))
			if_frequency = 6900000;  /*6.9MHz	*/
		else if (dev->norm & V4L2_STD_GH)
			if_frequency = 7100000;  /*7.1MHz	*/
		else if (dev->norm & V4L2_STD_PAL_I)
			if_frequency = 7250000;  /*7.25MHz	*/
		else if (dev->norm & V4L2_STD_SECAM_L)
			if_frequency = 6900000;  /*6.9MHz	*/
		else if (dev->norm & V4L2_STD_SECAM_LC)
			if_frequency = 1250000;  /*1.25MHz	*/

		cx231xx_info("if_frequency is set to %d\n", if_frequency);
		cx231xx_set_Colibri_For_LowIF(dev, if_frequency, 1, 1);

		update_HH_register_after_set_DIF(dev);
	}

	cx231xx_info("Set New FREQUENCY to %d\n", f->frequency);

	return rc;
}