#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_3__ {scalar_t__ muxingapp; } ;
typedef  TYPE_1__ MatroskaDemuxContext ;

/* Variables and functions */
 int AV_FIELD_BB ; 
 int AV_FIELD_BT ; 
 int AV_FIELD_PROGRESSIVE ; 
 int AV_FIELD_TB ; 
 int AV_FIELD_TT ; 
 int AV_FIELD_UNKNOWN ; 
#define  MATROSKA_VIDEO_FIELDORDER_BB 133 
#define  MATROSKA_VIDEO_FIELDORDER_BT 132 
#define  MATROSKA_VIDEO_FIELDORDER_PROGRESSIVE 131 
#define  MATROSKA_VIDEO_FIELDORDER_TB 130 
#define  MATROSKA_VIDEO_FIELDORDER_TT 129 
#define  MATROSKA_VIDEO_FIELDORDER_UNDETERMINED 128 
 int sscanf (scalar_t__,char*,int*,int*,int*) ; 

__attribute__((used)) static int mkv_field_order(MatroskaDemuxContext *matroska, int64_t field_order)
{
    int major, minor, micro, bttb = 0;

    /* workaround a bug in our Matroska muxer, introduced in version 57.36 alongside
     * this function, and fixed in 57.52 */
    if (matroska->muxingapp && sscanf(matroska->muxingapp, "Lavf%d.%d.%d", &major, &minor, &micro) == 3)
        bttb = (major == 57 && minor >= 36 && minor <= 51 && micro >= 100);

    switch (field_order) {
    case MATROSKA_VIDEO_FIELDORDER_PROGRESSIVE:
        return AV_FIELD_PROGRESSIVE;
    case MATROSKA_VIDEO_FIELDORDER_UNDETERMINED:
        return AV_FIELD_UNKNOWN;
    case MATROSKA_VIDEO_FIELDORDER_TT:
        return AV_FIELD_TT;
    case MATROSKA_VIDEO_FIELDORDER_BB:
        return AV_FIELD_BB;
    case MATROSKA_VIDEO_FIELDORDER_BT:
        return bttb ? AV_FIELD_TB : AV_FIELD_BT;
    case MATROSKA_VIDEO_FIELDORDER_TB:
        return bttb ? AV_FIELD_BT : AV_FIELD_TB;
    default:
        return AV_FIELD_UNKNOWN;
    }
}