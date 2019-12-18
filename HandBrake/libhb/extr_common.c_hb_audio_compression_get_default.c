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

float hb_audio_compression_get_default(uint32_t codec)
{
    switch (codec)
    {
        case HB_ACODEC_FFFLAC:
        case HB_ACODEC_FFFLAC24:
            return 5.;

        case HB_ACODEC_LAME:
            return 2.;

        case HB_ACODEC_OPUS:
            return 10.;

        default:
            return -1.;
    }
}