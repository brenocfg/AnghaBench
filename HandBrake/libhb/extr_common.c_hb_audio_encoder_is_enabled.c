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
 int /*<<< orphan*/  AV_CODEC_ID_AC3 ; 
 int /*<<< orphan*/  AV_CODEC_ID_EAC3 ; 
 int /*<<< orphan*/  AV_CODEC_ID_FLAC ; 
 int /*<<< orphan*/  AV_CODEC_ID_OPUS ; 
#define  HB_ACODEC_AC3 140 
#define  HB_ACODEC_CA_AAC 139 
#define  HB_ACODEC_CA_HAAC 138 
#define  HB_ACODEC_FDK_AAC 137 
#define  HB_ACODEC_FDK_HAAC 136 
#define  HB_ACODEC_FFAAC 135 
#define  HB_ACODEC_FFEAC3 134 
#define  HB_ACODEC_FFFLAC 133 
#define  HB_ACODEC_FFFLAC24 132 
#define  HB_ACODEC_LAME 131 
#define  HB_ACODEC_NONE 130 
#define  HB_ACODEC_OPUS 129 
 int HB_ACODEC_PASS_FLAG ; 
#define  HB_ACODEC_VORBIS 128 
 int /*<<< orphan*/ * avcodec_find_encoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * avcodec_find_encoder_by_name (char*) ; 

__attribute__((used)) static int hb_audio_encoder_is_enabled(int encoder)
{
    if (encoder & HB_ACODEC_PASS_FLAG)
    {
        // Passthru encoders are always enabled
        return 1;
    }
    switch (encoder)
    {
#ifdef __APPLE__
        case HB_ACODEC_CA_AAC:
        case HB_ACODEC_CA_HAAC:
            return 1;
#endif

#if HB_PROJECT_FEATURE_FFMPEG_AAC
        case HB_ACODEC_FFAAC:
            return avcodec_find_encoder_by_name("aac") != NULL;
#endif

        case HB_ACODEC_FDK_AAC:
        case HB_ACODEC_FDK_HAAC:
            return avcodec_find_encoder_by_name("libfdk_aac") != NULL;

        case HB_ACODEC_AC3:
            return avcodec_find_encoder(AV_CODEC_ID_AC3) != NULL;

        case HB_ACODEC_FFEAC3:
            return avcodec_find_encoder(AV_CODEC_ID_EAC3) != NULL;

        case HB_ACODEC_FFFLAC:
        case HB_ACODEC_FFFLAC24:
            return avcodec_find_encoder(AV_CODEC_ID_FLAC) != NULL;

        case HB_ACODEC_OPUS:
            return avcodec_find_encoder(AV_CODEC_ID_OPUS) != NULL;

        // the following encoders are always enabled
        case HB_ACODEC_LAME:
        case HB_ACODEC_VORBIS:
        case HB_ACODEC_NONE:
            return 1;

        default:
            return 0;
    }
}