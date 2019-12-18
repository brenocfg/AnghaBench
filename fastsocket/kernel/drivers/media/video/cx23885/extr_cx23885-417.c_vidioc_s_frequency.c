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
struct v4l2_frequency {scalar_t__ tuner; scalar_t__ type; int /*<<< orphan*/  frequency; } ;
struct file {struct cx23885_fh* private_data; } ;
struct cx23885_fh {struct cx23885_dev* dev; } ;
struct cx23885_dev {scalar_t__ tuner_type; int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_ENC_STOP_CAPTURE ; 
 int /*<<< orphan*/  CX23885_END_NOW ; 
 int /*<<< orphan*/  CX23885_MPEG_CAPTURE ; 
 int /*<<< orphan*/  CX23885_RAW_BITS_NONE ; 
 int EINVAL ; 
 scalar_t__ UNSET ; 
 scalar_t__ V4L2_TUNER_ANALOG_TV ; 
 int /*<<< orphan*/  call_all (struct cx23885_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  cx23885_api_cmd (struct cx23885_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx23885_initialize_codec (struct cx23885_dev*) ; 
 int /*<<< orphan*/  dprintk (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  tuner ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *priv,
				struct v4l2_frequency *f)
{
	struct cx23885_fh  *fh  = file->private_data;
	struct cx23885_dev *dev = fh->dev;

	cx23885_api_cmd(fh->dev, CX2341X_ENC_STOP_CAPTURE, 3, 0,
		CX23885_END_NOW, CX23885_MPEG_CAPTURE,
		CX23885_RAW_BITS_NONE);

	dprintk(1, "VIDIOC_S_FREQUENCY: dev type %d, f\n",
		dev->tuner_type);
	dprintk(1, "VIDIOC_S_FREQUENCY: f tuner %d, f type %d\n",
		f->tuner, f->type);
	if (UNSET == dev->tuner_type)
		return -EINVAL;
	if (f->tuner != 0)
		return -EINVAL;
	if (f->type != V4L2_TUNER_ANALOG_TV)
		return -EINVAL;
	dev->freq = f->frequency;

	call_all(dev, tuner, s_frequency, f);

	cx23885_initialize_codec(dev);

	return 0;
}