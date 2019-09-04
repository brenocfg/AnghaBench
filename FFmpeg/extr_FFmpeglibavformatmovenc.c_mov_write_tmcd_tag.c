#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_11__ {int /*<<< orphan*/  value; } ;
struct TYPE_10__ {int timescale; int timecode_flags; scalar_t__ mode; TYPE_2__* st; } ;
struct TYPE_8__ {int /*<<< orphan*/  num; int /*<<< orphan*/  den; } ;
struct TYPE_9__ {int /*<<< orphan*/  metadata; TYPE_1__ avg_frame_rate; } ;
typedef  TYPE_3__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVDictionaryEntry ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ MODE_MP4 ; 
 int ROUNDED_DIV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int av_rescale (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mov_write_source_reference_tag (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ utf8len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_tmcd_tag(AVIOContext *pb, MOVTrack *track)
{
    int64_t pos = avio_tell(pb);
#if 1
    int frame_duration;
    int nb_frames;
    AVDictionaryEntry *t = NULL;

    if (!track->st->avg_frame_rate.num || !track->st->avg_frame_rate.den) {
#if FF_API_LAVF_AVCTX
    FF_DISABLE_DEPRECATION_WARNINGS
        frame_duration = av_rescale(track->timescale, track->st->codec->time_base.num, track->st->codec->time_base.den);
        nb_frames      = ROUNDED_DIV(track->st->codec->time_base.den, track->st->codec->time_base.num);
    FF_ENABLE_DEPRECATION_WARNINGS
#else
        av_log(NULL, AV_LOG_ERROR, "avg_frame_rate not set for tmcd track.\n");
        return AVERROR(EINVAL);
#endif
    } else {
        frame_duration = av_rescale(track->timescale, track->st->avg_frame_rate.num, track->st->avg_frame_rate.den);
        nb_frames      = ROUNDED_DIV(track->st->avg_frame_rate.den, track->st->avg_frame_rate.num);
    }

    if (nb_frames > 255) {
        av_log(NULL, AV_LOG_ERROR, "fps %d is too large\n", nb_frames);
        return AVERROR(EINVAL);
    }

    avio_wb32(pb, 0); /* size */
    ffio_wfourcc(pb, "tmcd");               /* Data format */
    avio_wb32(pb, 0);                       /* Reserved */
    avio_wb32(pb, 1);                       /* Data reference index */
    avio_wb32(pb, 0);                       /* Flags */
    avio_wb32(pb, track->timecode_flags);   /* Flags (timecode) */
    avio_wb32(pb, track->timescale);        /* Timescale */
    avio_wb32(pb, frame_duration);          /* Frame duration */
    avio_w8(pb, nb_frames);                 /* Number of frames */
    avio_w8(pb, 0);                         /* Reserved */

    t = av_dict_get(track->st->metadata, "reel_name", NULL, 0);
    if (t && utf8len(t->value) && track->mode != MODE_MP4)
        mov_write_source_reference_tag(pb, track, t->value);
    else
        avio_wb16(pb, 0); /* zero size */
#else

    avio_wb32(pb, 0); /* size */
    ffio_wfourcc(pb, "tmcd");               /* Data format */
    avio_wb32(pb, 0);                       /* Reserved */
    avio_wb32(pb, 1);                       /* Data reference index */
    if (track->par->extradata_size)
        avio_write(pb, track->par->extradata, track->par->extradata_size);
#endif
    return update_size(pb, pos);
}