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
typedef  int /*<<< orphan*/  GXRModeObj ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_GetEuRGB60 () ; 
 scalar_t__ CONF_GetProgressiveScan () ; 
 int CONF_GetVideo () ; 
#define  CONF_VIDEO_MPAL 134 
#define  CONF_VIDEO_NTSC 133 
#define  CONF_VIDEO_PAL 132 
 int /*<<< orphan*/  TVEurgb60Hz480IntDf ; 
 int /*<<< orphan*/  TVEurgb60Hz480Prog ; 
 int /*<<< orphan*/  TVMpal480IntDf ; 
 int /*<<< orphan*/  TVMpal480Prog ; 
 int /*<<< orphan*/  TVNtsc480IntDf ; 
 int /*<<< orphan*/  TVNtsc480Prog ; 
 int /*<<< orphan*/  TVPal576IntDfScale ; 
 int /*<<< orphan*/  TVPal576ProgScale ; 
 int VIDEO_GetCurrentTvMode () ; 
 scalar_t__ VIDEO_HaveComponentCable () ; 
#define  VI_EURGB60 131 
#define  VI_MPAL 130 
#define  VI_NTSC 129 
#define  VI_PAL 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

GXRModeObj * VIDEO_GetPreferredMode(GXRModeObj *mode)
{

GXRModeObj *rmode = NULL;

#if defined(HW_RVL)
	u32 tvmode = CONF_GetVideo();
	if (CONF_GetProgressiveScan() > 0 && VIDEO_HaveComponentCable()) {
		switch (tvmode) {
			case CONF_VIDEO_NTSC:
				rmode = &TVNtsc480Prog;
				break;
			case CONF_VIDEO_PAL:
				if (CONF_GetEuRGB60() > 0)
					rmode = &TVEurgb60Hz480Prog;
				else rmode = &TVPal576ProgScale;
				break;
			case CONF_VIDEO_MPAL:
				rmode = &TVMpal480Prog;
				break;
			default:
				rmode = &TVNtsc480Prog;
		}
	} else {
		switch (tvmode) {
			case CONF_VIDEO_NTSC:
				rmode = &TVNtsc480IntDf;
				break;
			case CONF_VIDEO_PAL:
				if (CONF_GetEuRGB60() > 0)
					rmode = &TVEurgb60Hz480IntDf;
				else rmode = &TVPal576IntDfScale;
				break;
			case CONF_VIDEO_MPAL:
				rmode = &TVMpal480IntDf;
				break;
			default:
				rmode = &TVNtsc480IntDf;
		}
	}
#else
	u32 tvmode = VIDEO_GetCurrentTvMode();
	if (VIDEO_HaveComponentCable()) {
		switch (tvmode) {
			case VI_NTSC:
				rmode = &TVNtsc480Prog;
				break;
			case VI_PAL:
				rmode = &TVPal576ProgScale;
				break;
			case VI_MPAL:
				rmode = &TVMpal480Prog;
				break;
			case VI_EURGB60:
				rmode = &TVEurgb60Hz480Prog;
				break;
		}
	} else {
		switch (tvmode) {
			case VI_NTSC:
				rmode = &TVNtsc480IntDf;
				break;
			case VI_PAL:
				rmode = &TVPal576IntDfScale;
				break;
			case VI_MPAL:
				rmode = &TVMpal480IntDf;
				break;
			case VI_EURGB60:
				rmode = &TVEurgb60Hz480IntDf;
				break;
		}
	}
#endif

	if ( NULL != mode ) {
		memcpy( mode, rmode, sizeof(GXRModeObj));
	} else {
		mode = rmode;
	}

	return mode;

}