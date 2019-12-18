#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int height; scalar_t__ mode; TYPE_1__* par; } ;
struct TYPE_4__ {int color_primaries; int color_trc; int color_space; int width; int height; scalar_t__ color_range; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
#define  AVCOL_PRI_BT2020 145 
#define  AVCOL_PRI_BT470BG 144 
#define  AVCOL_PRI_BT709 143 
#define  AVCOL_PRI_SMPTE170M 142 
#define  AVCOL_PRI_SMPTE240M 141 
#define  AVCOL_PRI_SMPTE431 140 
#define  AVCOL_PRI_SMPTE432 139 
 int AVCOL_PRI_UNSPECIFIED ; 
 scalar_t__ AVCOL_RANGE_JPEG ; 
#define  AVCOL_SPC_BT2020_NCL 138 
#define  AVCOL_SPC_BT470BG 137 
#define  AVCOL_SPC_BT709 136 
#define  AVCOL_SPC_SMPTE170M 135 
#define  AVCOL_SPC_SMPTE240M 134 
 int AVCOL_SPC_UNSPECIFIED ; 
#define  AVCOL_TRC_ARIB_STD_B67 133 
#define  AVCOL_TRC_BT709 132 
#define  AVCOL_TRC_SMPTE170M 131 
#define  AVCOL_TRC_SMPTE240M 130 
#define  AVCOL_TRC_SMPTE428 129 
#define  AVCOL_TRC_SMPTEST2084 128 
 int AVCOL_TRC_UNSPECIFIED ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ MODE_MOV ; 
 scalar_t__ MODE_MP4 ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_colr_tag(AVIOContext *pb, MOVTrack *track)
{
    int64_t pos = avio_tell(pb);

    // Ref (MOV): https://developer.apple.com/library/mac/technotes/tn2162/_index.html#//apple_ref/doc/uid/DTS40013070-CH1-TNTAG9
    // Ref (MP4): ISO/IEC 14496-12:2012

    if (track->par->color_primaries == AVCOL_PRI_UNSPECIFIED &&
        track->par->color_trc == AVCOL_TRC_UNSPECIFIED &&
        track->par->color_space == AVCOL_SPC_UNSPECIFIED) {
        if ((track->par->width >= 1920 && track->par->height >= 1080)
          || (track->par->width == 1280 && track->par->height == 720)) {
            av_log(NULL, AV_LOG_WARNING, "color primaries unspecified, assuming bt709\n");
            track->par->color_primaries = AVCOL_PRI_BT709;
        } else if (track->par->width == 720 && track->height == 576) {
            av_log(NULL, AV_LOG_WARNING, "color primaries unspecified, assuming bt470bg\n");
            track->par->color_primaries = AVCOL_PRI_BT470BG;
        } else if (track->par->width == 720 &&
                   (track->height == 486 || track->height == 480)) {
            av_log(NULL, AV_LOG_WARNING, "color primaries unspecified, assuming smpte170\n");
            track->par->color_primaries = AVCOL_PRI_SMPTE170M;
        } else {
            av_log(NULL, AV_LOG_WARNING, "color primaries unspecified, unable to assume anything\n");
        }
        switch (track->par->color_primaries) {
        case AVCOL_PRI_BT709:
            track->par->color_trc = AVCOL_TRC_BT709;
            track->par->color_space = AVCOL_SPC_BT709;
            break;
        case AVCOL_PRI_SMPTE170M:
        case AVCOL_PRI_BT470BG:
            track->par->color_trc = AVCOL_TRC_BT709;
            track->par->color_space = AVCOL_SPC_SMPTE170M;
            break;
        }
    }

    /* We should only ever be called by MOV or MP4. */
    av_assert0(track->mode == MODE_MOV || track->mode == MODE_MP4);

    avio_wb32(pb, 0); /* size */
    ffio_wfourcc(pb, "colr");
    if (track->mode == MODE_MP4)
        ffio_wfourcc(pb, "nclx");
    else
        ffio_wfourcc(pb, "nclc");
    switch (track->par->color_primaries) {
    case AVCOL_PRI_BT709:     avio_wb16(pb, 1); break;
    case AVCOL_PRI_BT470BG:   avio_wb16(pb, 5); break;
    case AVCOL_PRI_SMPTE170M:
    case AVCOL_PRI_SMPTE240M: avio_wb16(pb, 6); break;
    case AVCOL_PRI_BT2020:    avio_wb16(pb, 9); break;
    case AVCOL_PRI_SMPTE431:  avio_wb16(pb, 11); break;
    case AVCOL_PRI_SMPTE432:  avio_wb16(pb, 12); break;
    default:                  avio_wb16(pb, 2);
    }
    switch (track->par->color_trc) {
    case AVCOL_TRC_BT709:        avio_wb16(pb, 1); break;
    case AVCOL_TRC_SMPTE170M:    avio_wb16(pb, 1); break; // remapped
    case AVCOL_TRC_SMPTE240M:    avio_wb16(pb, 7); break;
    case AVCOL_TRC_SMPTEST2084:  avio_wb16(pb, 16); break;
    case AVCOL_TRC_SMPTE428:     avio_wb16(pb, 17); break;
    case AVCOL_TRC_ARIB_STD_B67: avio_wb16(pb, 18); break;
    default:                     avio_wb16(pb, 2);
    }
    switch (track->par->color_space) {
    case AVCOL_SPC_BT709:      avio_wb16(pb, 1); break;
    case AVCOL_SPC_BT470BG:
    case AVCOL_SPC_SMPTE170M:  avio_wb16(pb, 6); break;
    case AVCOL_SPC_SMPTE240M:  avio_wb16(pb, 7); break;
    case AVCOL_SPC_BT2020_NCL: avio_wb16(pb, 9); break;
    default:                   avio_wb16(pb, 2);
    }

    if (track->mode == MODE_MP4) {
        int full_range = track->par->color_range == AVCOL_RANGE_JPEG;
        avio_w8(pb, full_range << 7);
    }

    return update_size(pb, pos);
}