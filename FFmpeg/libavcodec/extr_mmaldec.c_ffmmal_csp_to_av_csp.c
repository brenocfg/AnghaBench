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
typedef  int MMAL_FOURCC_T ;

/* Variables and functions */
 int AVCOL_SPC_BT470BG ; 
 int AVCOL_SPC_BT709 ; 
 int AVCOL_SPC_FCC ; 
 int AVCOL_SPC_SMPTE240M ; 
 int AVCOL_SPC_UNSPECIFIED ; 
#define  MMAL_COLOR_SPACE_BT470_2_BG 133 
#define  MMAL_COLOR_SPACE_BT470_2_M 132 
#define  MMAL_COLOR_SPACE_FCC 131 
#define  MMAL_COLOR_SPACE_ITUR_BT601 130 
#define  MMAL_COLOR_SPACE_ITUR_BT709 129 
#define  MMAL_COLOR_SPACE_SMPTE240M 128 

__attribute__((used)) static enum AVColorSpace ffmmal_csp_to_av_csp(MMAL_FOURCC_T fourcc)
{
    switch (fourcc) {
    case MMAL_COLOR_SPACE_BT470_2_BG:
    case MMAL_COLOR_SPACE_BT470_2_M:
    case MMAL_COLOR_SPACE_ITUR_BT601:   return AVCOL_SPC_BT470BG;
    case MMAL_COLOR_SPACE_ITUR_BT709:   return AVCOL_SPC_BT709;
    case MMAL_COLOR_SPACE_FCC:          return AVCOL_SPC_FCC;
    case MMAL_COLOR_SPACE_SMPTE240M:    return AVCOL_SPC_SMPTE240M;
    default:                            return AVCOL_SPC_UNSPECIFIED;
    }
}