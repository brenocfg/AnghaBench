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
#define  AVCOL_SPC_BT2020_CL 140 
#define  AVCOL_SPC_BT2020_NCL 139 
#define  AVCOL_SPC_BT470BG 138 
#define  AVCOL_SPC_BT709 137 
#define  AVCOL_SPC_CHROMA_DERIVED_CL 136 
#define  AVCOL_SPC_CHROMA_DERIVED_NCL 135 
#define  AVCOL_SPC_FCC 134 
#define  AVCOL_SPC_ICTCP 133 
#define  AVCOL_SPC_RGB 132 
#define  AVCOL_SPC_SMPTE170M 131 
#define  AVCOL_SPC_SMPTE240M 130 
#define  AVCOL_SPC_UNSPECIFIED 129 
#define  AVCOL_SPC_YCGCO 128 
 int ZIMG_MATRIX_170M ; 
 int ZIMG_MATRIX_2020_CL ; 
 int ZIMG_MATRIX_2020_NCL ; 
 int ZIMG_MATRIX_240M ; 
 int ZIMG_MATRIX_470BG ; 
 int ZIMG_MATRIX_709 ; 
 int ZIMG_MATRIX_CHROMATICITY_DERIVED_CL ; 
 int ZIMG_MATRIX_CHROMATICITY_DERIVED_NCL ; 
 int ZIMG_MATRIX_FCC ; 
 int ZIMG_MATRIX_ICTCP ; 
 int ZIMG_MATRIX_RGB ; 
 int ZIMG_MATRIX_UNSPECIFIED ; 
 int ZIMG_MATRIX_YCGCO ; 

__attribute__((used)) static int convert_matrix(enum AVColorSpace colorspace)
{
    switch (colorspace) {
    case AVCOL_SPC_RGB:
        return ZIMG_MATRIX_RGB;
    case AVCOL_SPC_BT709:
        return ZIMG_MATRIX_709;
    case AVCOL_SPC_UNSPECIFIED:
        return ZIMG_MATRIX_UNSPECIFIED;
    case AVCOL_SPC_FCC:
        return ZIMG_MATRIX_FCC;
    case AVCOL_SPC_BT470BG:
        return ZIMG_MATRIX_470BG;
    case AVCOL_SPC_SMPTE170M:
        return ZIMG_MATRIX_170M;
    case AVCOL_SPC_SMPTE240M:
        return ZIMG_MATRIX_240M;
    case AVCOL_SPC_YCGCO:
        return ZIMG_MATRIX_YCGCO;
    case AVCOL_SPC_BT2020_NCL:
        return ZIMG_MATRIX_2020_NCL;
    case AVCOL_SPC_BT2020_CL:
        return ZIMG_MATRIX_2020_CL;
    case AVCOL_SPC_CHROMA_DERIVED_NCL:
        return ZIMG_MATRIX_CHROMATICITY_DERIVED_NCL;
    case AVCOL_SPC_CHROMA_DERIVED_CL:
        return ZIMG_MATRIX_CHROMATICITY_DERIVED_CL;
    case AVCOL_SPC_ICTCP:
        return ZIMG_MATRIX_ICTCP;
    }
    return ZIMG_MATRIX_UNSPECIFIED;
}