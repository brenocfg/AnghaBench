#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_12__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_11__ {TYPE_2__** streams; TYPE_3__* priv_data; } ;
struct TYPE_10__ {int n_videos; int n_audios; int n_subtitles; TYPE_6__** subtitles; TYPE_6__** audios; TYPE_6__** videos; scalar_t__ is_live; } ;
struct TYPE_8__ {int /*<<< orphan*/  den; } ;
struct TYPE_9__ {TYPE_1__ time_base; } ;
typedef  TYPE_3__ DASHContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVSEEK_FLAG_BACKWARD ; 
 int AVSEEK_FLAG_BYTE ; 
 int /*<<< orphan*/  AV_ROUND_DOWN ; 
 int /*<<< orphan*/  AV_ROUND_UP ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  av_rescale_rnd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dash_seek (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int dash_read_seek(AVFormatContext *s, int stream_index, int64_t timestamp, int flags)
{
    int ret = 0, i;
    DASHContext *c = s->priv_data;
    int64_t seek_pos_msec = av_rescale_rnd(timestamp, 1000,
                                           s->streams[stream_index]->time_base.den,
                                           flags & AVSEEK_FLAG_BACKWARD ?
                                           AV_ROUND_DOWN : AV_ROUND_UP);
    if ((flags & AVSEEK_FLAG_BYTE) || c->is_live)
        return AVERROR(ENOSYS);

    /* Seek in discarded streams with dry_run=1 to avoid reopening them */
    for (i = 0; i < c->n_videos; i++) {
        if (!ret)
            ret = dash_seek(s, c->videos[i], seek_pos_msec, flags, !c->videos[i]->ctx);
    }
    for (i = 0; i < c->n_audios; i++) {
        if (!ret)
            ret = dash_seek(s, c->audios[i], seek_pos_msec, flags, !c->audios[i]->ctx);
    }
    for (i = 0; i < c->n_subtitles; i++) {
        if (!ret)
            ret = dash_seek(s, c->subtitles[i], seek_pos_msec, flags, !c->subtitles[i]->ctx);
    }

    return ret;
}