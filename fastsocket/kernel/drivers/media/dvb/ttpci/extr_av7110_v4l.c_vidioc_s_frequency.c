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
struct v4l2_frequency {scalar_t__ type; int /*<<< orphan*/  frequency; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct file {int dummy; } ;
struct av7110 {int analog_tuner_flags; int current_input; int /*<<< orphan*/  current_freq; } ;

/* Variables and functions */
 int ANALOG_TUNER_STV0297 ; 
 int ANALOG_TUNER_VES1820 ; 
 int EINVAL ; 
 int /*<<< orphan*/  MSP_WR_DSP ; 
 scalar_t__ V4L2_TUNER_ANALOG_TV ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msp_writereg (struct av7110*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stv0297_set_tv_freq (struct saa7146_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ves1820_set_tv_freq (struct saa7146_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *fh, struct v4l2_frequency *f)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct av7110 *av7110 = (struct av7110 *)dev->ext_priv;

	dprintk(2, "VIDIOC_S_FREQUENCY: freq:0x%08x.\n", f->frequency);

	if (!av7110->analog_tuner_flags || av7110->current_input != 1)
		return -EINVAL;

	if (V4L2_TUNER_ANALOG_TV != f->type)
		return -EINVAL;

	msp_writereg(av7110, MSP_WR_DSP, 0x0000, 0xffe0); /* fast mute */
	msp_writereg(av7110, MSP_WR_DSP, 0x0007, 0xffe0);

	/* tune in desired frequency */
	if (av7110->analog_tuner_flags & ANALOG_TUNER_VES1820)
		ves1820_set_tv_freq(dev, f->frequency);
	else if (av7110->analog_tuner_flags & ANALOG_TUNER_STV0297)
		stv0297_set_tv_freq(dev, f->frequency);
	av7110->current_freq = f->frequency;

	msp_writereg(av7110, MSP_WR_DSP, 0x0015, 0x003f); /* start stereo detection */
	msp_writereg(av7110, MSP_WR_DSP, 0x0015, 0x0000);
	msp_writereg(av7110, MSP_WR_DSP, 0x0000, 0x4f00); /* loudspeaker + headphone */
	msp_writereg(av7110, MSP_WR_DSP, 0x0007, 0x4f00); /* SCART 1 volume */
	return 0;
}