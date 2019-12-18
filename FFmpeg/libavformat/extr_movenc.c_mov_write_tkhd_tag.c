#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int64_t ;
struct TYPE_19__ {scalar_t__ value; } ;
struct TYPE_14__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_18__ {int index; TYPE_2__ sample_aspect_ratio; scalar_t__ metadata; TYPE_1__* codecpar; } ;
struct TYPE_17__ {scalar_t__ mode; int /*<<< orphan*/  fc; scalar_t__ per_stream_grouping; } ;
struct TYPE_16__ {int flags; scalar_t__ mode; int time; int track_id; scalar_t__ height; TYPE_3__* par; int /*<<< orphan*/  entry; int /*<<< orphan*/  timescale; int /*<<< orphan*/  track_duration; } ;
struct TYPE_15__ {scalar_t__ codec_type; scalar_t__ height; scalar_t__ width; } ;
struct TYPE_13__ {int codec_type; } ;
typedef  TYPE_4__ MOVTrack ;
typedef  TYPE_5__ MOVMuxContext ;
typedef  TYPE_6__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_7__ AVDictionaryEntry ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_SUBTITLE ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PKT_DATA_DISPLAYMATRIX ; 
 int /*<<< orphan*/  AV_ROUND_UP ; 
 int INT32_MAX ; 
 scalar_t__ MODE_ISM ; 
 scalar_t__ MODE_MOV ; 
 int /*<<< orphan*/  MOV_TIMESCALE ; 
 int MOV_TKHD_FLAG_ENABLED ; 
 int MOV_TKHD_FLAG_IN_MOVIE ; 
 int MOV_TRACK_ENABLED ; 
 int UINT32_MAX ; 
 int UINT64_C (int) ; 
 int atoi (scalar_t__) ; 
 TYPE_7__* av_dict_get (scalar_t__,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int av_rescale (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int av_rescale_rnd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ av_stream_get_side_data (TYPE_6__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  write_matrix (int /*<<< orphan*/ *,int,int,int,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int mov_write_tkhd_tag(AVIOContext *pb, MOVMuxContext *mov,
                              MOVTrack *track, AVStream *st)
{
    int64_t duration = av_rescale_rnd(track->track_duration, MOV_TIMESCALE,
                                      track->timescale, AV_ROUND_UP);
    int version = duration < INT32_MAX ? 0 : 1;
    int flags   = MOV_TKHD_FLAG_IN_MOVIE;
    int rotation = 0;
    int group   = 0;

    uint32_t *display_matrix = NULL;
    int      display_matrix_size, i;

    if (st) {
        if (mov->per_stream_grouping)
            group = st->index;
        else
            group = st->codecpar->codec_type;

        display_matrix = (uint32_t*)av_stream_get_side_data(st, AV_PKT_DATA_DISPLAYMATRIX,
                                                            &display_matrix_size);
        if (display_matrix && display_matrix_size < 9 * sizeof(*display_matrix))
            display_matrix = NULL;
    }

    if (track->flags & MOV_TRACK_ENABLED)
        flags |= MOV_TKHD_FLAG_ENABLED;

    if (track->mode == MODE_ISM)
        version = 1;

    (version == 1) ? avio_wb32(pb, 104) : avio_wb32(pb, 92); /* size */
    ffio_wfourcc(pb, "tkhd");
    avio_w8(pb, version);
    avio_wb24(pb, flags);
    if (version == 1) {
        avio_wb64(pb, track->time);
        avio_wb64(pb, track->time);
    } else {
        avio_wb32(pb, track->time); /* creation time */
        avio_wb32(pb, track->time); /* modification time */
    }
    avio_wb32(pb, track->track_id); /* track-id */
    avio_wb32(pb, 0); /* reserved */
    if (!track->entry && mov->mode == MODE_ISM)
        (version == 1) ? avio_wb64(pb, UINT64_C(0xffffffffffffffff)) : avio_wb32(pb, 0xffffffff);
    else if (!track->entry)
        (version == 1) ? avio_wb64(pb, 0) : avio_wb32(pb, 0);
    else
        (version == 1) ? avio_wb64(pb, duration) : avio_wb32(pb, duration);

    avio_wb32(pb, 0); /* reserved */
    avio_wb32(pb, 0); /* reserved */
    avio_wb16(pb, 0); /* layer */
    avio_wb16(pb, group); /* alternate group) */
    /* Volume, only for audio */
    if (track->par->codec_type == AVMEDIA_TYPE_AUDIO)
        avio_wb16(pb, 0x0100);
    else
        avio_wb16(pb, 0);
    avio_wb16(pb, 0); /* reserved */

    /* Matrix structure */
#if FF_API_OLD_ROTATE_API
    if (st && st->metadata) {
        AVDictionaryEntry *rot = av_dict_get(st->metadata, "rotate", NULL, 0);
        rotation = (rot && rot->value) ? atoi(rot->value) : 0;
    }
#endif
    if (display_matrix) {
        for (i = 0; i < 9; i++)
            avio_wb32(pb, display_matrix[i]);
#if FF_API_OLD_ROTATE_API
    } else if (rotation == 90) {
        write_matrix(pb,  0,  1, -1,  0, track->par->height, 0);
    } else if (rotation == 180) {
        write_matrix(pb, -1,  0,  0, -1, track->par->width, track->par->height);
    } else if (rotation == 270) {
        write_matrix(pb,  0, -1,  1,  0, 0, track->par->width);
#endif
    } else {
        write_matrix(pb,  1,  0,  0,  1, 0, 0);
    }
    /* Track width and height, for visual only */
    if (st && (track->par->codec_type == AVMEDIA_TYPE_VIDEO ||
               track->par->codec_type == AVMEDIA_TYPE_SUBTITLE)) {
        int64_t track_width_1616;
        if (track->mode == MODE_MOV) {
            track_width_1616 = track->par->width * 0x10000ULL;
        } else {
            track_width_1616 = av_rescale(st->sample_aspect_ratio.num,
                                                  track->par->width * 0x10000LL,
                                                  st->sample_aspect_ratio.den);
            if (!track_width_1616 ||
                track->height != track->par->height ||
                track_width_1616 > UINT32_MAX)
                track_width_1616 = track->par->width * 0x10000ULL;
        }
        if (track_width_1616 > UINT32_MAX) {
            av_log(mov->fc, AV_LOG_WARNING, "track width is too large\n");
            track_width_1616 = 0;
        }
        avio_wb32(pb, track_width_1616);
        if (track->height > 0xFFFF) {
            av_log(mov->fc, AV_LOG_WARNING, "track height is too large\n");
            avio_wb32(pb, 0);
        } else
            avio_wb32(pb, track->height * 0x10000U);
    } else {
        avio_wb32(pb, 0);
        avio_wb32(pb, 0);
    }
    return 0x5c;
}