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
#define  HB_ACODEC_FFFLAC 131 
#define  HB_ACODEC_FFFLAC24 130 
#define  HB_ACODEC_LAME 129 
#define  HB_ACODEC_OPUS 128 

void hb_audio_compression_get_limits(uint32_t codec, float *low, float *high,
                                     float *granularity, int *direction)
{
    switch (codec)
    {
        case HB_ACODEC_FFFLAC:
        case HB_ACODEC_FFFLAC24:
            *direction   = 0;
            *granularity = 1.;
            *high        = 12.;
            *low         = 0.;
            break;

        case HB_ACODEC_LAME:
            *direction   = 1;
            *granularity = 1.;
            *high        = 9.;
            *low         = 0.;
            break;

        case HB_ACODEC_OPUS:
            *direction   = 0;
            *granularity = 1.;
            *high        = 10.;
            *low         = 0.;
            break;

        default:
            *direction   = 0;
            *granularity = 1.;
            *low = *high = -1.;
            break;
    }
}