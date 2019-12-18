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

/* Variables and functions */
#define  AFMT_QUERY 131 
#define  AFMT_S16_LE 130 
#define  AFMT_S8 129 
#define  AFMT_U8 128 
 int /*<<< orphan*/  vidc_audio_channels ; 
 unsigned int vidc_audio_format ; 
 int /*<<< orphan*/  vidc_update_filler (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int vidc_audio_set_format(int dev, unsigned int fmt)
{
	switch (fmt) {
	default:
		fmt = AFMT_S16_LE;
	case AFMT_U8:
	case AFMT_S8:
	case AFMT_S16_LE:
		vidc_audio_format = fmt;
		vidc_update_filler(vidc_audio_format, vidc_audio_channels);
	case AFMT_QUERY:
		break;
	}
	return vidc_audio_format;
}