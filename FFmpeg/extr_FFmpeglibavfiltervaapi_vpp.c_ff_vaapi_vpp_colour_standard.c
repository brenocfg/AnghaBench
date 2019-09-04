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
typedef  enum AVColorSpace { ____Placeholder_AVColorSpace } AVColorSpace ;

/* Variables and functions */
#define  AVCOL_SPC_BT470BG 131 
#define  AVCOL_SPC_BT709 130 
#define  AVCOL_SPC_SMPTE170M 129 
#define  AVCOL_SPC_SMPTE240M 128 
 int VAProcColorStandardBT601 ; 
 int VAProcColorStandardBT709 ; 
 int VAProcColorStandardNone ; 
 int VAProcColorStandardSMPTE170M ; 
 int VAProcColorStandardSMPTE240M ; 

int ff_vaapi_vpp_colour_standard(enum AVColorSpace av_cs)
{
    switch(av_cs) {
#define CS(av, va) case AVCOL_SPC_ ## av: return VAProcColorStandard ## va;
        CS(BT709,     BT709);
        CS(BT470BG,   BT601);
        CS(SMPTE170M, SMPTE170M);
        CS(SMPTE240M, SMPTE240M);
#undef CS
    default:
        return VAProcColorStandardNone;
    }
}