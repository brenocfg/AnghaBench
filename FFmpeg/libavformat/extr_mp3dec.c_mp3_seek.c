#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_16__ {int flags; TYPE_1__* internal; int /*<<< orphan*/  pb; TYPE_3__** streams; TYPE_2__* priv_data; } ;
struct TYPE_15__ {int timestamp; scalar_t__ pos; } ;
struct TYPE_14__ {scalar_t__ duration; TYPE_4__* index_entries; } ;
struct TYPE_13__ {scalar_t__ header_filesize; scalar_t__ frames; scalar_t__ is_cbr; scalar_t__ usetoc; scalar_t__ xing_toc; } ;
struct TYPE_12__ {scalar_t__ data_offset; } ;
typedef  TYPE_2__ MP3DecContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVIndexEntry ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVFMT_FLAG_FAST_SEEK ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ av_clip64 (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ av_index_search_timestamp (TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int av_rescale (scalar_t__,int,scalar_t__) ; 
 scalar_t__ avio_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_update_cur_dts (TYPE_5__*,TYPE_3__*,int) ; 
 scalar_t__ mp3_sync (TYPE_5__*,scalar_t__,int) ; 

__attribute__((used)) static int mp3_seek(AVFormatContext *s, int stream_index, int64_t timestamp,
                    int flags)
{
    MP3DecContext *mp3 = s->priv_data;
    AVIndexEntry *ie, ie1;
    AVStream *st = s->streams[0];
    int64_t best_pos;
    int fast_seek = s->flags & AVFMT_FLAG_FAST_SEEK;
    int64_t filesize = mp3->header_filesize;

    if (filesize <= 0) {
        int64_t size = avio_size(s->pb);
        if (size > 0 && size > s->internal->data_offset)
            filesize = size - s->internal->data_offset;
    }

    if (mp3->xing_toc && (mp3->usetoc || (fast_seek && !mp3->is_cbr))) {
        int64_t ret = av_index_search_timestamp(st, timestamp, flags);

        // NOTE: The MP3 TOC is not a precise lookup table. Accuracy is worse
        // for bigger files.
        av_log(s, AV_LOG_WARNING, "Using MP3 TOC to seek; may be imprecise.\n");

        if (ret < 0)
            return ret;

        ie = &st->index_entries[ret];
    } else if (fast_seek && st->duration > 0 && filesize > 0) {
        if (!mp3->is_cbr)
            av_log(s, AV_LOG_WARNING, "Using scaling to seek VBR MP3; may be imprecise.\n");

        ie = &ie1;
        timestamp = av_clip64(timestamp, 0, st->duration);
        ie->timestamp = timestamp;
        ie->pos       = av_rescale(timestamp, filesize, st->duration) + s->internal->data_offset;
    } else {
        return -1; // generic index code
    }

    best_pos = mp3_sync(s, ie->pos, flags);
    if (best_pos < 0)
        return best_pos;

    if (mp3->is_cbr && ie == &ie1 && mp3->frames) {
        int frame_duration = av_rescale(st->duration, 1, mp3->frames);
        ie1.timestamp = frame_duration * av_rescale(best_pos - s->internal->data_offset, mp3->frames, mp3->header_filesize);
    }

    ff_update_cur_dts(s, st, ie->timestamp);
    return 0;
}