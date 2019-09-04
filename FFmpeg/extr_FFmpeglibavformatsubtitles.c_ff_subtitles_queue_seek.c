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
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {scalar_t__ nb_subs; int current_sub_idx; TYPE_1__* subs; } ;
struct TYPE_5__ {scalar_t__ pts; int stream_index; scalar_t__ duration; } ;
typedef  TYPE_2__ FFDemuxSubtitlesQueue ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVSEEK_FLAG_BYTE ; 
 int AVSEEK_FLAG_FRAME ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  ERANGE ; 
 int search_sub_ts (TYPE_2__*,scalar_t__) ; 

int ff_subtitles_queue_seek(FFDemuxSubtitlesQueue *q, AVFormatContext *s, int stream_index,
                            int64_t min_ts, int64_t ts, int64_t max_ts, int flags)
{
    if (flags & AVSEEK_FLAG_BYTE) {
        return AVERROR(ENOSYS);
    } else if (flags & AVSEEK_FLAG_FRAME) {
        if (ts < 0 || ts >= q->nb_subs)
            return AVERROR(ERANGE);
        q->current_sub_idx = ts;
    } else {
        int i, idx = search_sub_ts(q, ts);
        int64_t ts_selected;

        if (idx < 0)
            return idx;
        for (i = idx; i < q->nb_subs && q->subs[i].pts < min_ts; i++)
            if (stream_index == -1 || q->subs[i].stream_index == stream_index)
                idx = i;
        for (i = idx; i > 0 && q->subs[i].pts > max_ts; i--)
            if (stream_index == -1 || q->subs[i].stream_index == stream_index)
                idx = i;

        ts_selected = q->subs[idx].pts;
        if (ts_selected < min_ts || ts_selected > max_ts)
            return AVERROR(ERANGE);

        /* look back in the latest subtitles for overlapping subtitles */
        for (i = idx - 1; i >= 0; i--) {
            int64_t pts = q->subs[i].pts;
            if (q->subs[i].duration <= 0 ||
                (stream_index != -1 && q->subs[i].stream_index != stream_index))
                continue;
            if (pts >= min_ts && pts > ts_selected - q->subs[i].duration)
                idx = i;
            else
                break;
        }

        /* If the queue is used to store multiple subtitles streams (like with
         * VobSub) and the stream index is not specified, we need to make sure
         * to focus on the smallest file position offset for a same timestamp;
         * queue is ordered by pts and then filepos, so we can take the first
         * entry for a given timestamp. */
        if (stream_index == -1)
            while (idx > 0 && q->subs[idx - 1].pts == q->subs[idx].pts)
                idx--;

        q->current_sub_idx = idx;
    }
    return 0;
}