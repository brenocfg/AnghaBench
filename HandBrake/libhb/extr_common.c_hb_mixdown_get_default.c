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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
#define  HB_ACODEC_AC3 137 
#define  HB_ACODEC_CA_AAC 136 
#define  HB_ACODEC_CA_HAAC 135 
#define  HB_ACODEC_FDK_AAC 134 
#define  HB_ACODEC_FDK_HAAC 133 
#define  HB_ACODEC_FFAAC 132 
#define  HB_ACODEC_FFEAC3 131 
#define  HB_ACODEC_FFFLAC 130 
#define  HB_ACODEC_FFFLAC24 129 
#define  HB_ACODEC_OPUS 128 
 int HB_AMIXDOWN_5POINT1 ; 
 int HB_AMIXDOWN_7POINT1 ; 
 int HB_AMIXDOWN_DOLBYPLII ; 
 int hb_mixdown_get_best (int,int /*<<< orphan*/ ,int) ; 

int hb_mixdown_get_default(uint32_t codec, uint64_t layout)
{
    int mixdown;
    switch (codec)
    {
        // the FLAC encoder defaults to the best mixdown up to 7.1
        case HB_ACODEC_FFFLAC:
        case HB_ACODEC_FFFLAC24:
        case HB_ACODEC_OPUS:
        case HB_ACODEC_CA_AAC:
        case HB_ACODEC_CA_HAAC:
        case HB_ACODEC_FFAAC:
        case HB_ACODEC_FDK_AAC:
        case HB_ACODEC_FDK_HAAC:
            mixdown = HB_AMIXDOWN_7POINT1;
            break;

        // the (E-)AC-3 encoder defaults to the best mixdown up to 5.1
        case HB_ACODEC_AC3:
        case HB_ACODEC_FFEAC3:
            mixdown = HB_AMIXDOWN_5POINT1;
            break;

        // other encoders default to the best mixdown up to DPLII
        default:
            mixdown = HB_AMIXDOWN_DOLBYPLII;
            break;
    }

    // return the best available mixdown up to the selected default
    return hb_mixdown_get_best(codec, layout, mixdown);
}