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
struct saa7134_dev {size_t board; } ;
struct TYPE_2__ {int video_out; unsigned int vid_port_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_VIDEO_PORT_CTRL0 ; 
 int /*<<< orphan*/  SAA7134_VIDEO_PORT_CTRL1 ; 
 int /*<<< orphan*/  SAA7134_VIDEO_PORT_CTRL2 ; 
 int /*<<< orphan*/  SAA7134_VIDEO_PORT_CTRL3 ; 
 int /*<<< orphan*/  SAA7134_VIDEO_PORT_CTRL4 ; 
 int /*<<< orphan*/  SAA7134_VIDEO_PORT_CTRL5 ; 
 int /*<<< orphan*/  SAA7134_VIDEO_PORT_CTRL6 ; 
 int /*<<< orphan*/  SAA7134_VIDEO_PORT_CTRL7 ; 
 int /*<<< orphan*/  SAA7134_VIDEO_PORT_CTRL8 ; 
 unsigned int SET_CLOCK_INVERTED ; 
 unsigned int SET_CLOCK_NOT_DELAYED ; 
 unsigned int SET_T_CODE_POLARITY_NON_INVERTED ; 
 unsigned int SET_VSYNC_OFF ; 
 int VP_CLK_CTRL1_INVERTED ; 
 int VP_CLK_CTRL2_DELAYED ; 
 int VP_T_CODE_P_INVERTED ; 
 int VP_VS_TYPE_MASK ; 
 int VP_VS_TYPE_OFF ; 
 TYPE_1__* saa7134_boards ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 
 int** video_out ; 

int saa7134_videoport_init(struct saa7134_dev *dev)
{
	/* enable video output */
	int vo = saa7134_boards[dev->board].video_out;
	int video_reg;
	unsigned int vid_port_opts = saa7134_boards[dev->board].vid_port_opts;

	/* Configure videoport */
	saa_writeb(SAA7134_VIDEO_PORT_CTRL0, video_out[vo][0]);
	video_reg = video_out[vo][1];
	if (vid_port_opts & SET_T_CODE_POLARITY_NON_INVERTED)
		video_reg &= ~VP_T_CODE_P_INVERTED;
	saa_writeb(SAA7134_VIDEO_PORT_CTRL1, video_reg);
	saa_writeb(SAA7134_VIDEO_PORT_CTRL2, video_out[vo][2]);
	saa_writeb(SAA7134_VIDEO_PORT_CTRL4, video_out[vo][4]);
	video_reg = video_out[vo][5];
	if (vid_port_opts & SET_CLOCK_NOT_DELAYED)
		video_reg &= ~VP_CLK_CTRL2_DELAYED;
	if (vid_port_opts & SET_CLOCK_INVERTED)
		video_reg |= VP_CLK_CTRL1_INVERTED;
	saa_writeb(SAA7134_VIDEO_PORT_CTRL5, video_reg);
	video_reg = video_out[vo][6];
	if (vid_port_opts & SET_VSYNC_OFF) {
		video_reg &= ~VP_VS_TYPE_MASK;
		video_reg |= VP_VS_TYPE_OFF;
	}
	saa_writeb(SAA7134_VIDEO_PORT_CTRL6, video_reg);
	saa_writeb(SAA7134_VIDEO_PORT_CTRL7, video_out[vo][7]);
	saa_writeb(SAA7134_VIDEO_PORT_CTRL8, video_out[vo][8]);

	/* Start videoport */
	saa_writeb(SAA7134_VIDEO_PORT_CTRL3, video_out[vo][3]);

	return 0;
}