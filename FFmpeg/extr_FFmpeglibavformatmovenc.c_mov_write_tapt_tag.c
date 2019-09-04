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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int int32_t ;
struct TYPE_7__ {TYPE_2__* par; } ;
struct TYPE_5__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_6__ {int width; int height; TYPE_1__ sample_aspect_ratio; } ;
typedef  TYPE_3__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int av_rescale (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_tapt_tag(AVIOContext *pb, MOVTrack *track)
{
    int32_t width = av_rescale(track->par->sample_aspect_ratio.num, track->par->width,
                               track->par->sample_aspect_ratio.den);

    int64_t pos = avio_tell(pb);

    avio_wb32(pb, 0); /* size */
    ffio_wfourcc(pb, "tapt");

    avio_wb32(pb, 20);
    ffio_wfourcc(pb, "clef");
    avio_wb32(pb, 0);
    avio_wb32(pb, width << 16);
    avio_wb32(pb, track->par->height << 16);

    avio_wb32(pb, 20);
    ffio_wfourcc(pb, "prof");
    avio_wb32(pb, 0);
    avio_wb32(pb, width << 16);
    avio_wb32(pb, track->par->height << 16);

    avio_wb32(pb, 20);
    ffio_wfourcc(pb, "enof");
    avio_wb32(pb, 0);
    avio_wb32(pb, track->par->width << 16);
    avio_wb32(pb, track->par->height << 16);

    return update_size(pb, pos);
}