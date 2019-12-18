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
#define  HB_COLR_MAT_BT2020_NCL 135 
#define  HB_COLR_MAT_BT470BG 134 
#define  HB_COLR_MAT_BT709 133 
#define  HB_COLR_MAT_FCC 132 
#define  HB_COLR_MAT_RGB 131 
#define  HB_COLR_MAT_SMPTE170M 130 
#define  HB_COLR_MAT_SMPTE240M 129 
#define  HB_COLR_MAT_YCGCO 128 

const char * hb_get_matrix_name(int matrix)
{
    switch (matrix)
    {
        case HB_COLR_MAT_BT709:
            return "bt709";
        case HB_COLR_MAT_FCC:
            return "fcc";
        case HB_COLR_MAT_BT470BG:
            return "bt470bg";
        case HB_COLR_MAT_SMPTE170M:
            return "smpte170m";
        case HB_COLR_MAT_SMPTE240M:
            return "smpte240m";
        case HB_COLR_MAT_YCGCO:
            return "ycgco";
        case HB_COLR_MAT_RGB:
            return "gbr";
        case HB_COLR_MAT_BT2020_NCL:
            return "bt2020ncl";
        default:
            return NULL;
    }
}