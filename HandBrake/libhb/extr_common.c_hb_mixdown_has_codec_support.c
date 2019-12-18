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
#define  HB_ACODEC_CA_AAC 137 
#define  HB_ACODEC_CA_HAAC 136 
#define  HB_ACODEC_FDK_AAC 135 
#define  HB_ACODEC_FDK_HAAC 134 
#define  HB_ACODEC_FFAAC 133 
#define  HB_ACODEC_FFFLAC 132 
#define  HB_ACODEC_FFFLAC24 131 
#define  HB_ACODEC_LAME 130 
#define  HB_ACODEC_OPUS 129 
 int HB_ACODEC_PASS_FLAG ; 
#define  HB_ACODEC_VORBIS 128 
 int HB_AMIXDOWN_5POINT1 ; 
 int HB_AMIXDOWN_7POINT1 ; 
 int HB_AMIXDOWN_DOLBYPLII ; 
 int HB_AMIXDOWN_NONE ; 

int hb_mixdown_has_codec_support(int mixdown, uint32_t codec)
{
    // Passthru, only "None" mixdown is supported
    if (codec & HB_ACODEC_PASS_FLAG)
        return (mixdown == HB_AMIXDOWN_NONE);

    // Not passthru, "None" mixdown never supported
    if (mixdown == HB_AMIXDOWN_NONE)
        return 0;

    switch (codec)
    {
        case HB_ACODEC_VORBIS:
        case HB_ACODEC_FFFLAC:
        case HB_ACODEC_FFFLAC24:
        case HB_ACODEC_OPUS:
        case HB_ACODEC_CA_AAC:
        case HB_ACODEC_CA_HAAC:
        case HB_ACODEC_FFAAC:
            return (mixdown <= HB_AMIXDOWN_7POINT1);

        case HB_ACODEC_LAME:
            return (mixdown <= HB_AMIXDOWN_DOLBYPLII);

        case HB_ACODEC_FDK_AAC:
        case HB_ACODEC_FDK_HAAC:
            return ((mixdown <= HB_AMIXDOWN_5POINT1) ||
                    (mixdown == HB_AMIXDOWN_7POINT1));

        default:
            return (mixdown <= HB_AMIXDOWN_5POINT1);
    }
}