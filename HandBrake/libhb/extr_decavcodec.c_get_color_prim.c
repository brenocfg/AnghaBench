#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int den; } ;
typedef  TYPE_1__ hb_rational_t ;
struct TYPE_6__ {int width; int height; } ;
typedef  TYPE_2__ hb_geometry_t ;

/* Variables and functions */
#define  AVCOL_PRI_BT2020 138 
#define  AVCOL_PRI_BT470BG 137 
#define  AVCOL_PRI_BT470M 136 
#define  AVCOL_PRI_BT709 135 
#define  AVCOL_PRI_FILM 134 
#define  AVCOL_PRI_JEDEC_P22 133 
#define  AVCOL_PRI_SMPTE170M 132 
#define  AVCOL_PRI_SMPTE240M 131 
#define  AVCOL_PRI_SMPTE428 130 
#define  AVCOL_PRI_SMPTE431 129 
#define  AVCOL_PRI_SMPTE432 128 
 int HB_COLR_PRI_BT2020 ; 
 int HB_COLR_PRI_BT470M ; 
 int HB_COLR_PRI_BT709 ; 
 int HB_COLR_PRI_EBUTECH ; 
 int HB_COLR_PRI_FILM ; 
 int HB_COLR_PRI_JEDEC_P22 ; 
 int HB_COLR_PRI_SMPTE428 ; 
 int HB_COLR_PRI_SMPTE431 ; 
 int HB_COLR_PRI_SMPTE432 ; 
 int HB_COLR_PRI_SMPTEC ; 

__attribute__((used)) static int get_color_prim(int color_primaries, hb_geometry_t geometry, hb_rational_t rate)
{
    switch (color_primaries)
    {
        case AVCOL_PRI_BT709:
            return HB_COLR_PRI_BT709;
        case AVCOL_PRI_BT470M:
            return HB_COLR_PRI_BT470M;
        case AVCOL_PRI_BT470BG:
            return HB_COLR_PRI_EBUTECH;
        case AVCOL_PRI_SMPTE170M:
        case AVCOL_PRI_SMPTE240M:
            return HB_COLR_PRI_SMPTEC;
        case AVCOL_PRI_FILM:
            return HB_COLR_PRI_FILM;
        case AVCOL_PRI_SMPTE428:
            return HB_COLR_PRI_SMPTE428;
        case AVCOL_PRI_SMPTE431:
            return HB_COLR_PRI_SMPTE431;
        case AVCOL_PRI_SMPTE432:
            return HB_COLR_PRI_SMPTE432;
        case AVCOL_PRI_JEDEC_P22:
            return HB_COLR_PRI_JEDEC_P22;
        case AVCOL_PRI_BT2020:
            return HB_COLR_PRI_BT2020;
        default:
        {
            if ((geometry.width >= 1280 || geometry.height >= 720)||
                (geometry.width >   720 && geometry.height >  576 ))
                // ITU BT.709 HD content
                return HB_COLR_PRI_BT709;
            else if (rate.den == 1080000)
                // ITU BT.601 DVD or SD TV content (PAL)
                return HB_COLR_PRI_EBUTECH;
            else
                // ITU BT.601 DVD or SD TV content (NTSC)
                return HB_COLR_PRI_SMPTEC;
        }
    }
}