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
struct videobuf_queue {struct em28xx_fh* priv_data; } ;
struct v4l2_frequency {int /*<<< orphan*/  type; int /*<<< orphan*/  frequency; } ;
struct em28xx_fh {scalar_t__ radio; struct em28xx* dev; } ;
struct em28xx {int width; int height; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  ctl_freq; TYPE_1__* format; } ;
typedef  int /*<<< orphan*/  f ;
struct TYPE_2__ {int depth; } ;

/* Variables and functions */
 unsigned int EM28XX_DEF_BUF ; 
 unsigned int EM28XX_MIN_BUF ; 
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  memset (struct v4l2_frequency*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 

__attribute__((used)) static int
buffer_setup(struct videobuf_queue *vq, unsigned int *count, unsigned int *size)
{
	struct em28xx_fh *fh = vq->priv_data;
	struct em28xx        *dev = fh->dev;
	struct v4l2_frequency f;

	*size = (fh->dev->width * fh->dev->height * dev->format->depth + 7)
		>> 3;

	if (0 == *count)
		*count = EM28XX_DEF_BUF;

	if (*count < EM28XX_MIN_BUF)
		*count = EM28XX_MIN_BUF;

	/* Ask tuner to go to analog or radio mode */
	memset(&f, 0, sizeof(f));
	f.frequency = dev->ctl_freq;
	f.type = fh->radio ? V4L2_TUNER_RADIO : V4L2_TUNER_ANALOG_TV;

	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, s_frequency, &f);

	return 0;
}