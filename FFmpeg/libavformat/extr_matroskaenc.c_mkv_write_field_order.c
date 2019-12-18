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
typedef  enum AVFieldOrder { ____Placeholder_AVFieldOrder } AVFieldOrder ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
#define  AV_FIELD_BB 133 
#define  AV_FIELD_BT 132 
#define  AV_FIELD_PROGRESSIVE 131 
#define  AV_FIELD_TB 130 
#define  AV_FIELD_TT 129 
#define  AV_FIELD_UNKNOWN 128 
 int /*<<< orphan*/  MATROSKA_ID_VIDEOFIELDORDER ; 
 int /*<<< orphan*/  MATROSKA_ID_VIDEOFLAGINTERLACED ; 
 int /*<<< orphan*/  MATROSKA_VIDEO_FIELDORDER_BB ; 
 int /*<<< orphan*/  MATROSKA_VIDEO_FIELDORDER_BT ; 
 int /*<<< orphan*/  MATROSKA_VIDEO_FIELDORDER_TB ; 
 int /*<<< orphan*/  MATROSKA_VIDEO_FIELDORDER_TT ; 
 int /*<<< orphan*/  MATROSKA_VIDEO_INTERLACE_FLAG_INTERLACED ; 
 int /*<<< orphan*/  MATROSKA_VIDEO_INTERLACE_FLAG_PROGRESSIVE ; 
 int MODE_WEBM ; 
 int /*<<< orphan*/  put_ebml_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mkv_write_field_order(AVIOContext *pb, int mode,
                                  enum AVFieldOrder field_order)
{
    switch (field_order) {
    case AV_FIELD_UNKNOWN:
        break;
    case AV_FIELD_PROGRESSIVE:
        put_ebml_uint(pb, MATROSKA_ID_VIDEOFLAGINTERLACED,
                      MATROSKA_VIDEO_INTERLACE_FLAG_PROGRESSIVE);
        break;
    case AV_FIELD_TT:
    case AV_FIELD_BB:
    case AV_FIELD_TB:
    case AV_FIELD_BT:
        put_ebml_uint(pb, MATROSKA_ID_VIDEOFLAGINTERLACED,
                      MATROSKA_VIDEO_INTERLACE_FLAG_INTERLACED);
        if (mode != MODE_WEBM) {
            switch (field_order) {
            case AV_FIELD_TT:
                put_ebml_uint(pb, MATROSKA_ID_VIDEOFIELDORDER,
                              MATROSKA_VIDEO_FIELDORDER_TT);
                break;
            case AV_FIELD_BB:
                put_ebml_uint(pb, MATROSKA_ID_VIDEOFIELDORDER,
                              MATROSKA_VIDEO_FIELDORDER_BB);
                break;
            case AV_FIELD_TB:
                put_ebml_uint(pb, MATROSKA_ID_VIDEOFIELDORDER,
                              MATROSKA_VIDEO_FIELDORDER_TB);
                break;
            case AV_FIELD_BT:
                put_ebml_uint(pb, MATROSKA_ID_VIDEOFIELDORDER,
                              MATROSKA_VIDEO_FIELDORDER_BT);
                break;
            }
        }
    }
}