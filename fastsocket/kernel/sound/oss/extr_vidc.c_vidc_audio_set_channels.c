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
 short vidc_audio_channels ; 
 int /*<<< orphan*/  vidc_audio_format ; 
 int /*<<< orphan*/  vidc_update_filler (int /*<<< orphan*/ ,short) ; 

__attribute__((used)) static short vidc_audio_set_channels(int dev, short channels)
{
	switch (channels) {
	default:
		channels = 2;
	case 1:
	case 2:
		vidc_audio_channels = channels;
		vidc_update_filler(vidc_audio_format, vidc_audio_channels);
	case 0:
		break;
	}
	return vidc_audio_channels;
}