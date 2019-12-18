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
#define  AVCOL_SPC_BT2020_CL 142 
#define  AVCOL_SPC_BT2020_NCL 141 
#define  AVCOL_SPC_BT470BG 140 
#define  AVCOL_SPC_BT709 139 
#define  AVCOL_SPC_CHROMA_DERIVED_CL 138 
#define  AVCOL_SPC_CHROMA_DERIVED_NCL 137 
#define  AVCOL_SPC_FCC 136 
#define  AVCOL_SPC_ICTCP 135 
#define  AVCOL_SPC_RESERVED 134 
#define  AVCOL_SPC_RGB 133 
#define  AVCOL_SPC_SMPTE170M 132 
#define  AVCOL_SPC_SMPTE2085 131 
#define  AVCOL_SPC_SMPTE240M 130 
#define  AVCOL_SPC_UNSPECIFIED 129 
#define  AVCOL_SPC_YCGCO 128 
 int HB_COLR_MAT_BT2020_CL ; 
 int HB_COLR_MAT_BT2020_NCL ; 
 int HB_COLR_MAT_BT470BG ; 
 int HB_COLR_MAT_BT709 ; 
 int HB_COLR_MAT_CD_CL ; 
 int HB_COLR_MAT_CD_NCL ; 
 int HB_COLR_MAT_FCC ; 
 int HB_COLR_MAT_ICTCP ; 
 int HB_COLR_MAT_RGB ; 
 int HB_COLR_MAT_SMPTE170M ; 
 int HB_COLR_MAT_SMPTE2085 ; 
 int HB_COLR_MAT_SMPTE240M ; 
 int HB_COLR_MAT_UNDEF ; 
 int HB_COLR_MAT_YCGCO ; 

int hb_colr_mat_ff_to_hb(int colr_mat)
{
    switch (colr_mat)
    {
        case AVCOL_SPC_RGB:
            return HB_COLR_MAT_RGB;
        case AVCOL_SPC_BT709:
            return HB_COLR_MAT_BT709;
        case AVCOL_SPC_FCC:
            return HB_COLR_MAT_FCC;
        case AVCOL_SPC_BT470BG:
            return HB_COLR_MAT_BT470BG;
        case AVCOL_SPC_SMPTE170M:
            return HB_COLR_MAT_SMPTE170M;
        case AVCOL_SPC_SMPTE240M:
            return HB_COLR_MAT_SMPTE240M;
        case AVCOL_SPC_YCGCO:
            return HB_COLR_MAT_YCGCO;
        case AVCOL_SPC_BT2020_NCL:
            return HB_COLR_MAT_BT2020_NCL;
        case AVCOL_SPC_BT2020_CL:
            return HB_COLR_MAT_BT2020_CL;
        case AVCOL_SPC_SMPTE2085:
            return HB_COLR_MAT_SMPTE2085;
        case AVCOL_SPC_CHROMA_DERIVED_NCL:
            return HB_COLR_MAT_CD_NCL;
        case AVCOL_SPC_CHROMA_DERIVED_CL:
            return HB_COLR_MAT_CD_CL;
        case AVCOL_SPC_ICTCP:
            return HB_COLR_MAT_ICTCP;
        default:
        case AVCOL_SPC_UNSPECIFIED:
        case AVCOL_SPC_RESERVED:
            return HB_COLR_MAT_UNDEF;
    }
}