#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* vos_data; int vos_len; scalar_t__ tag; TYPE_2__* par; } ;
struct TYPE_5__ {int num; int den; } ;
struct TYPE_6__ {int width; scalar_t__ color_range; int height; TYPE_1__ sample_aspect_ratio; } ;
typedef  TYPE_3__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 scalar_t__ AVCOL_RANGE_MPEG ; 
 scalar_t__ AVCOL_RANGE_UNSPECIFIED ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_RB32 (int*) ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_dnxhd_parse_header_prefix (int*) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int mov_write_avid_tag(AVIOContext *pb, MOVTrack *track)
{
    int i;
    int interlaced;
    int cid;
    int display_width = track->par->width;

    if (track->vos_data && track->vos_len > 0x29) {
        if (ff_dnxhd_parse_header_prefix(track->vos_data) != 0) {
            /* looks like a DNxHD bit stream */
            interlaced = (track->vos_data[5] & 2);
            cid = AV_RB32(track->vos_data + 0x28);
        } else {
            av_log(NULL, AV_LOG_WARNING, "Could not locate DNxHD bit stream in vos_data\n");
            return 0;
        }
    } else {
        av_log(NULL, AV_LOG_WARNING, "Could not locate DNxHD bit stream, vos_data too small\n");
        return 0;
    }

    avio_wb32(pb, 24); /* size */
    ffio_wfourcc(pb, "ACLR");
    ffio_wfourcc(pb, "ACLR");
    ffio_wfourcc(pb, "0001");
    if (track->par->color_range == AVCOL_RANGE_MPEG || /* Legal range (16-235) */
        track->par->color_range == AVCOL_RANGE_UNSPECIFIED) {
        avio_wb32(pb, 1); /* Corresponds to 709 in official encoder */
    } else { /* Full range (0-255) */
        avio_wb32(pb, 2); /* Corresponds to RGB in official encoder */
    }
    avio_wb32(pb, 0); /* unknown */

    if (track->tag == MKTAG('A','V','d','h')) {
        avio_wb32(pb, 32);
        ffio_wfourcc(pb, "ADHR");
        ffio_wfourcc(pb, "0001");
        avio_wb32(pb, cid);
        avio_wb32(pb, 0); /* unknown */
        avio_wb32(pb, 1); /* unknown */
        avio_wb32(pb, 0); /* unknown */
        avio_wb32(pb, 0); /* unknown */
        return 0;
    }

    avio_wb32(pb, 24); /* size */
    ffio_wfourcc(pb, "APRG");
    ffio_wfourcc(pb, "APRG");
    ffio_wfourcc(pb, "0001");
    avio_wb32(pb, 1); /* unknown */
    avio_wb32(pb, 0); /* unknown */

    avio_wb32(pb, 120); /* size */
    ffio_wfourcc(pb, "ARES");
    ffio_wfourcc(pb, "ARES");
    ffio_wfourcc(pb, "0001");
    avio_wb32(pb, cid); /* dnxhd cid, some id ? */
    if (   track->par->sample_aspect_ratio.num > 0
        && track->par->sample_aspect_ratio.den > 0)
        display_width = display_width * track->par->sample_aspect_ratio.num / track->par->sample_aspect_ratio.den;
    avio_wb32(pb, display_width);
    /* values below are based on samples created with quicktime and avid codecs */
    if (interlaced) {
        avio_wb32(pb, track->par->height / 2);
        avio_wb32(pb, 2); /* unknown */
        avio_wb32(pb, 0); /* unknown */
        avio_wb32(pb, 4); /* unknown */
    } else {
        avio_wb32(pb, track->par->height);
        avio_wb32(pb, 1); /* unknown */
        avio_wb32(pb, 0); /* unknown */
        if (track->par->height == 1080)
            avio_wb32(pb, 5); /* unknown */
        else
            avio_wb32(pb, 6); /* unknown */
    }
    /* padding */
    for (i = 0; i < 10; i++)
        avio_wb64(pb, 0);

    return 0;
}