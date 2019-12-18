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
 int AVCOL_SPC_BT2020_CL ; 
 int AVCOL_SPC_BT2020_NCL ; 
 int AVCOL_SPC_BT470BG ; 
 int AVCOL_SPC_BT709 ; 
 int AVCOL_SPC_CHROMA_DERIVED_CL ; 
 int AVCOL_SPC_CHROMA_DERIVED_NCL ; 
 int AVCOL_SPC_FCC ; 
 int AVCOL_SPC_ICTCP ; 
 int AVCOL_SPC_RGB ; 
 int AVCOL_SPC_SMPTE170M ; 
 int AVCOL_SPC_SMPTE2085 ; 
 int AVCOL_SPC_SMPTE240M ; 
 int AVCOL_SPC_UNSPECIFIED ; 
 int AVCOL_SPC_YCGCO ; 
#define  HB_COLR_MAT_BT2020_CL 141 
#define  HB_COLR_MAT_BT2020_NCL 140 
#define  HB_COLR_MAT_BT470BG 139 
#define  HB_COLR_MAT_BT709 138 
#define  HB_COLR_MAT_CD_CL 137 
#define  HB_COLR_MAT_CD_NCL 136 
#define  HB_COLR_MAT_FCC 135 
#define  HB_COLR_MAT_ICTCP 134 
#define  HB_COLR_MAT_RGB 133 
#define  HB_COLR_MAT_SMPTE170M 132 
#define  HB_COLR_MAT_SMPTE2085 131 
#define  HB_COLR_MAT_SMPTE240M 130 
#define  HB_COLR_MAT_UNDEF 129 
#define  HB_COLR_MAT_YCGCO 128 

int hb_colr_mat_hb_to_ff(int colr_mat)
{
    switch (colr_mat)
    {
        case HB_COLR_MAT_RGB:
            return AVCOL_SPC_RGB;
        case HB_COLR_MAT_BT709:
            return AVCOL_SPC_BT709;
        case HB_COLR_MAT_FCC:
            return AVCOL_SPC_FCC;
        case HB_COLR_MAT_BT470BG:
            return AVCOL_SPC_BT470BG;
        case HB_COLR_MAT_SMPTE170M:
            return AVCOL_SPC_SMPTE170M;
        case HB_COLR_MAT_SMPTE240M:
            return AVCOL_SPC_SMPTE240M;
        case HB_COLR_MAT_YCGCO:
            return AVCOL_SPC_YCGCO;
        case HB_COLR_MAT_BT2020_NCL:
            return AVCOL_SPC_BT2020_NCL;
        case HB_COLR_MAT_BT2020_CL:
            return AVCOL_SPC_BT2020_CL;
        case HB_COLR_MAT_SMPTE2085:
            return AVCOL_SPC_SMPTE2085;
        case HB_COLR_MAT_CD_NCL:
            return AVCOL_SPC_CHROMA_DERIVED_NCL;
        case HB_COLR_MAT_CD_CL:
            return AVCOL_SPC_CHROMA_DERIVED_CL;
        case HB_COLR_MAT_ICTCP:
            return AVCOL_SPC_ICTCP;
        default:
        case HB_COLR_MAT_UNDEF:
            return AVCOL_SPC_UNSPECIFIED;
    }
}