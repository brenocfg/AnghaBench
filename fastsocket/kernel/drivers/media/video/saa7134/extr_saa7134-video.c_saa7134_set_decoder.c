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
struct saa7134_tvnorm {int luma_control; int sync_control; int src_timing; int chroma_ctrl1; int chroma_gain; int chroma_ctrl2; int vgate_misc; } ;
struct saa7134_dev {int ctl_bright; int ctl_contrast; int ctl_saturation; int ctl_hue; scalar_t__ ctl_invert; scalar_t__ nosignal; int /*<<< orphan*/  ctl_input; struct saa7134_tvnorm* tvnorm; } ;
struct TYPE_2__ {int vmux; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_ANALOG_ADC ; 
 int /*<<< orphan*/  SAA7134_ANALOG_IN_CTRL1 ; 
 int /*<<< orphan*/  SAA7134_ANALOG_IN_CTRL2 ; 
 int /*<<< orphan*/  SAA7134_ANALOG_IN_CTRL3 ; 
 int /*<<< orphan*/  SAA7134_ANALOG_IN_CTRL4 ; 
 int /*<<< orphan*/  SAA7134_CHROMA_CTRL1 ; 
 int /*<<< orphan*/  SAA7134_CHROMA_CTRL2 ; 
 int /*<<< orphan*/  SAA7134_CHROMA_GAIN ; 
 int /*<<< orphan*/  SAA7134_DEC_CHROMA_HUE ; 
 int /*<<< orphan*/  SAA7134_DEC_CHROMA_SATURATION ; 
 int /*<<< orphan*/  SAA7134_DEC_LUMA_BRIGHT ; 
 int /*<<< orphan*/  SAA7134_DEC_LUMA_CONTRAST ; 
 int /*<<< orphan*/  SAA7134_HSYNC_START ; 
 int /*<<< orphan*/  SAA7134_HSYNC_STOP ; 
 int /*<<< orphan*/  SAA7134_INCR_DELAY ; 
 int /*<<< orphan*/  SAA7134_LUMA_CTRL ; 
 int /*<<< orphan*/  SAA7134_MISC_VGATE_MSB ; 
 int /*<<< orphan*/  SAA7134_MODE_DELAY_CTRL ; 
 int /*<<< orphan*/  SAA7134_RAW_DATA_GAIN ; 
 int /*<<< orphan*/  SAA7134_RAW_DATA_OFFSET ; 
 int /*<<< orphan*/  SAA7134_SOURCE_TIMING1 ; 
 int /*<<< orphan*/  SAA7134_SYNC_CTRL ; 
 int /*<<< orphan*/  SAA7134_VGATE_START ; 
 int /*<<< orphan*/  SAA7134_VGATE_STOP ; 
 TYPE_1__ card_in (struct saa7134_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ noninterlaced ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void saa7134_set_decoder(struct saa7134_dev *dev)
{
	int luma_control, sync_control, mux;

	struct saa7134_tvnorm *norm = dev->tvnorm;
	mux = card_in(dev, dev->ctl_input).vmux;

	luma_control = norm->luma_control;
	sync_control = norm->sync_control;

	if (mux > 5)
		luma_control |= 0x80; /* svideo */
	if (noninterlaced || dev->nosignal)
		sync_control |= 0x20;

	/* setup video decoder */
	saa_writeb(SAA7134_INCR_DELAY,            0x08);
	saa_writeb(SAA7134_ANALOG_IN_CTRL1,       0xc0 | mux);
	saa_writeb(SAA7134_ANALOG_IN_CTRL2,       0x00);

	saa_writeb(SAA7134_ANALOG_IN_CTRL3,       0x90);
	saa_writeb(SAA7134_ANALOG_IN_CTRL4,       0x90);
	saa_writeb(SAA7134_HSYNC_START,           0xeb);
	saa_writeb(SAA7134_HSYNC_STOP,            0xe0);
	saa_writeb(SAA7134_SOURCE_TIMING1,        norm->src_timing);

	saa_writeb(SAA7134_SYNC_CTRL,             sync_control);
	saa_writeb(SAA7134_LUMA_CTRL,             luma_control);
	saa_writeb(SAA7134_DEC_LUMA_BRIGHT,       dev->ctl_bright);

	saa_writeb(SAA7134_DEC_LUMA_CONTRAST,
		dev->ctl_invert ? -dev->ctl_contrast : dev->ctl_contrast);

	saa_writeb(SAA7134_DEC_CHROMA_SATURATION,
		dev->ctl_invert ? -dev->ctl_saturation : dev->ctl_saturation);

	saa_writeb(SAA7134_DEC_CHROMA_HUE,        dev->ctl_hue);
	saa_writeb(SAA7134_CHROMA_CTRL1,          norm->chroma_ctrl1);
	saa_writeb(SAA7134_CHROMA_GAIN,           norm->chroma_gain);

	saa_writeb(SAA7134_CHROMA_CTRL2,          norm->chroma_ctrl2);
	saa_writeb(SAA7134_MODE_DELAY_CTRL,       0x00);

	saa_writeb(SAA7134_ANALOG_ADC,            0x01);
	saa_writeb(SAA7134_VGATE_START,           0x11);
	saa_writeb(SAA7134_VGATE_STOP,            0xfe);
	saa_writeb(SAA7134_MISC_VGATE_MSB,        norm->vgate_misc);
	saa_writeb(SAA7134_RAW_DATA_GAIN,         0x40);
	saa_writeb(SAA7134_RAW_DATA_OFFSET,       0x80);
}