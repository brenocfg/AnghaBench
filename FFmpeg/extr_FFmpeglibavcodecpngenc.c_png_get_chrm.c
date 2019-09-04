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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum AVColorPrimaries { ____Placeholder_AVColorPrimaries } AVColorPrimaries ;

/* Variables and functions */
#define  AVCOL_PRI_BT2020 133 
#define  AVCOL_PRI_BT470BG 132 
#define  AVCOL_PRI_BT470M 131 
#define  AVCOL_PRI_BT709 130 
#define  AVCOL_PRI_SMPTE170M 129 
#define  AVCOL_PRI_SMPTE240M 128 
 int /*<<< orphan*/  AV_WB32_PNG (int /*<<< orphan*/ *,double) ; 

__attribute__((used)) static int png_get_chrm(enum AVColorPrimaries prim,  uint8_t *buf)
{
    double rx, ry, gx, gy, bx, by, wx = 0.3127, wy = 0.3290;
    switch (prim) {
        case AVCOL_PRI_BT709:
            rx = 0.640; ry = 0.330;
            gx = 0.300; gy = 0.600;
            bx = 0.150; by = 0.060;
            break;
        case AVCOL_PRI_BT470M:
            rx = 0.670; ry = 0.330;
            gx = 0.210; gy = 0.710;
            bx = 0.140; by = 0.080;
            wx = 0.310; wy = 0.316;
            break;
        case AVCOL_PRI_BT470BG:
            rx = 0.640; ry = 0.330;
            gx = 0.290; gy = 0.600;
            bx = 0.150; by = 0.060;
            break;
        case AVCOL_PRI_SMPTE170M:
        case AVCOL_PRI_SMPTE240M:
            rx = 0.630; ry = 0.340;
            gx = 0.310; gy = 0.595;
            bx = 0.155; by = 0.070;
            break;
        case AVCOL_PRI_BT2020:
            rx = 0.708; ry = 0.292;
            gx = 0.170; gy = 0.797;
            bx = 0.131; by = 0.046;
            break;
        default:
            return 0;
    }

    AV_WB32_PNG(buf     , wx); AV_WB32_PNG(buf + 4 , wy);
    AV_WB32_PNG(buf + 8 , rx); AV_WB32_PNG(buf + 12, ry);
    AV_WB32_PNG(buf + 16, gx); AV_WB32_PNG(buf + 20, gy);
    AV_WB32_PNG(buf + 24, bx); AV_WB32_PNG(buf + 28, by);
    return 1;
}