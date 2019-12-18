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

float hb_audio_quality_get_default(uint32_t codec)
{
    switch (codec)
    {
        case HB_ACODEC_FFAAC:
            return 5.;

        case HB_ACODEC_FDK_HAAC:
        case HB_ACODEC_FDK_AAC:
            return 3.;

        case HB_ACODEC_LAME:
            return 2.;

        case HB_ACODEC_VORBIS:
            return 5.;

        case HB_ACODEC_CA_AAC:
            return 91.;

        default:
            return HB_INVALID_AUDIO_QUALITY;
    }
}