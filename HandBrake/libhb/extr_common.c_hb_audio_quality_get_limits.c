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
typedef  int uint32_t ;

/* Variables and functions */
#define  HB_ACODEC_CA_AAC 133 
#define  HB_ACODEC_FDK_AAC 132 
#define  HB_ACODEC_FDK_HAAC 131 
#define  HB_ACODEC_FFAAC 130 
#define  HB_ACODEC_LAME 129 
#define  HB_ACODEC_VORBIS 128 
 float HB_INVALID_AUDIO_QUALITY ; 

void hb_audio_quality_get_limits(uint32_t codec, float *low, float *high,
                                 float *granularity, int *direction)
{
    switch (codec)
    {
        case HB_ACODEC_FFAAC:
            *direction   = 0;
            *granularity = 1.;
            *low         = 1.;
            *high        = 10.;
            break;

        case HB_ACODEC_FDK_HAAC:
        case HB_ACODEC_FDK_AAC:
            *direction   = 0;
            *granularity = 1.;
            *low         = 1.;
            *high        = 5.;
            break;

        case HB_ACODEC_LAME:
            *direction   = 1;
            *granularity = 0.5;
            *low         = 0.;
            *high        = 10.;
            break;

        case HB_ACODEC_VORBIS:
            *direction   = 0;
            *granularity = 0.5;
            *low         = -2.;
            *high        = 10.;
            break;

        case HB_ACODEC_CA_AAC:
            *direction   = 0;
            *granularity = 9.;
            *low         = 1.;
            *high        = 127.;
            break;

        default:
            *direction   = 0;
            *granularity = 1.;
            *low = *high = HB_INVALID_AUDIO_QUALITY;
            break;
    }
}