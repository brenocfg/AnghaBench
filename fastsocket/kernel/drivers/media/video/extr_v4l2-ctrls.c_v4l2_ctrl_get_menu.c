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

/* Variables and functions */
#define  V4L2_CID_COLORFX 146 
#define  V4L2_CID_EXPOSURE_AUTO 145 
#define  V4L2_CID_MPEG_AUDIO_AC3_BITRATE 144 
#define  V4L2_CID_MPEG_AUDIO_CRC 143 
#define  V4L2_CID_MPEG_AUDIO_EMPHASIS 142 
#define  V4L2_CID_MPEG_AUDIO_ENCODING 141 
#define  V4L2_CID_MPEG_AUDIO_L1_BITRATE 140 
#define  V4L2_CID_MPEG_AUDIO_L2_BITRATE 139 
#define  V4L2_CID_MPEG_AUDIO_L3_BITRATE 138 
#define  V4L2_CID_MPEG_AUDIO_MODE 137 
#define  V4L2_CID_MPEG_AUDIO_MODE_EXTENSION 136 
#define  V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ 135 
#define  V4L2_CID_MPEG_STREAM_TYPE 134 
#define  V4L2_CID_MPEG_STREAM_VBI_FMT 133 
#define  V4L2_CID_MPEG_VIDEO_ASPECT 132 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_MODE 131 
#define  V4L2_CID_MPEG_VIDEO_ENCODING 130 
#define  V4L2_CID_POWER_LINE_FREQUENCY 129 
#define  V4L2_CID_TUNE_PREEMPHASIS 128 

const char * const *v4l2_ctrl_get_menu(u32 id)
{
	static const char * const mpeg_audio_sampling_freq[] = {
		"44.1 kHz",
		"48 kHz",
		"32 kHz",
		NULL
	};
	static const char * const mpeg_audio_encoding[] = {
		"MPEG-1/2 Layer I",
		"MPEG-1/2 Layer II",
		"MPEG-1/2 Layer III",
		"MPEG-2/4 AAC",
		"AC-3",
		NULL
	};
	static const char * const mpeg_audio_l1_bitrate[] = {
		"32 kbps",
		"64 kbps",
		"96 kbps",
		"128 kbps",
		"160 kbps",
		"192 kbps",
		"224 kbps",
		"256 kbps",
		"288 kbps",
		"320 kbps",
		"352 kbps",
		"384 kbps",
		"416 kbps",
		"448 kbps",
		NULL
	};
	static const char * const mpeg_audio_l2_bitrate[] = {
		"32 kbps",
		"48 kbps",
		"56 kbps",
		"64 kbps",
		"80 kbps",
		"96 kbps",
		"112 kbps",
		"128 kbps",
		"160 kbps",
		"192 kbps",
		"224 kbps",
		"256 kbps",
		"320 kbps",
		"384 kbps",
		NULL
	};
	static const char * const mpeg_audio_l3_bitrate[] = {
		"32 kbps",
		"40 kbps",
		"48 kbps",
		"56 kbps",
		"64 kbps",
		"80 kbps",
		"96 kbps",
		"112 kbps",
		"128 kbps",
		"160 kbps",
		"192 kbps",
		"224 kbps",
		"256 kbps",
		"320 kbps",
		NULL
	};
	static const char * const mpeg_audio_ac3_bitrate[] = {
		"32 kbps",
		"40 kbps",
		"48 kbps",
		"56 kbps",
		"64 kbps",
		"80 kbps",
		"96 kbps",
		"112 kbps",
		"128 kbps",
		"160 kbps",
		"192 kbps",
		"224 kbps",
		"256 kbps",
		"320 kbps",
		"384 kbps",
		"448 kbps",
		"512 kbps",
		"576 kbps",
		"640 kbps",
		NULL
	};
	static const char * const mpeg_audio_mode[] = {
		"Stereo",
		"Joint Stereo",
		"Dual",
		"Mono",
		NULL
	};
	static const char * const mpeg_audio_mode_extension[] = {
		"Bound 4",
		"Bound 8",
		"Bound 12",
		"Bound 16",
		NULL
	};
	static const char * const mpeg_audio_emphasis[] = {
		"No Emphasis",
		"50/15 us",
		"CCITT J17",
		NULL
	};
	static const char * const mpeg_audio_crc[] = {
		"No CRC",
		"16-bit CRC",
		NULL
	};
	static const char * const mpeg_video_encoding[] = {
		"MPEG-1",
		"MPEG-2",
		"MPEG-4 AVC",
		NULL
	};
	static const char * const mpeg_video_aspect[] = {
		"1x1",
		"4x3",
		"16x9",
		"2.21x1",
		NULL
	};
	static const char * const mpeg_video_bitrate_mode[] = {
		"Variable Bitrate",
		"Constant Bitrate",
		NULL
	};
	static const char * const mpeg_stream_type[] = {
		"MPEG-2 Program Stream",
		"MPEG-2 Transport Stream",
		"MPEG-1 System Stream",
		"MPEG-2 DVD-compatible Stream",
		"MPEG-1 VCD-compatible Stream",
		"MPEG-2 SVCD-compatible Stream",
		NULL
	};
	static const char * const mpeg_stream_vbi_fmt[] = {
		"No VBI",
		"Private packet, IVTV format",
		NULL
	};
	static const char * const camera_power_line_frequency[] = {
		"Disabled",
		"50 Hz",
		"60 Hz",
		NULL
	};
	static const char * const camera_exposure_auto[] = {
		"Auto Mode",
		"Manual Mode",
		"Shutter Priority Mode",
		"Aperture Priority Mode",
		NULL
	};
	static const char * const colorfx[] = {
		"None",
		"Black & White",
		"Sepia",
		"Negative",
		"Emboss",
		"Sketch",
		"Sky blue",
		"Grass green",
		"Skin whiten",
		"Vivid",
		NULL
	};
	static const char * const tune_preemphasis[] = {
		"No preemphasis",
		"50 useconds",
		"75 useconds",
		NULL,
	};

	switch (id) {
	case V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ:
		return mpeg_audio_sampling_freq;
	case V4L2_CID_MPEG_AUDIO_ENCODING:
		return mpeg_audio_encoding;
	case V4L2_CID_MPEG_AUDIO_L1_BITRATE:
		return mpeg_audio_l1_bitrate;
	case V4L2_CID_MPEG_AUDIO_L2_BITRATE:
		return mpeg_audio_l2_bitrate;
	case V4L2_CID_MPEG_AUDIO_L3_BITRATE:
		return mpeg_audio_l3_bitrate;
	case V4L2_CID_MPEG_AUDIO_AC3_BITRATE:
		return mpeg_audio_ac3_bitrate;
	case V4L2_CID_MPEG_AUDIO_MODE:
		return mpeg_audio_mode;
	case V4L2_CID_MPEG_AUDIO_MODE_EXTENSION:
		return mpeg_audio_mode_extension;
	case V4L2_CID_MPEG_AUDIO_EMPHASIS:
		return mpeg_audio_emphasis;
	case V4L2_CID_MPEG_AUDIO_CRC:
		return mpeg_audio_crc;
	case V4L2_CID_MPEG_VIDEO_ENCODING:
		return mpeg_video_encoding;
	case V4L2_CID_MPEG_VIDEO_ASPECT:
		return mpeg_video_aspect;
	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		return mpeg_video_bitrate_mode;
	case V4L2_CID_MPEG_STREAM_TYPE:
		return mpeg_stream_type;
	case V4L2_CID_MPEG_STREAM_VBI_FMT:
		return mpeg_stream_vbi_fmt;
	case V4L2_CID_POWER_LINE_FREQUENCY:
		return camera_power_line_frequency;
	case V4L2_CID_EXPOSURE_AUTO:
		return camera_exposure_auto;
	case V4L2_CID_COLORFX:
		return colorfx;
	case V4L2_CID_TUNE_PREEMPHASIS:
		return tune_preemphasis;
	default:
		return NULL;
	}
}