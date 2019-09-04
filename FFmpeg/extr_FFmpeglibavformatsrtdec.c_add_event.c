#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct event_info {int x1; int y1; int x2; int y2; int /*<<< orphan*/  duration; int /*<<< orphan*/  pts; int /*<<< orphan*/  pos; } ;
struct TYPE_9__ {int len; char* str; } ;
struct TYPE_8__ {int /*<<< orphan*/  duration; int /*<<< orphan*/  pts; int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  FFDemuxSubtitlesQueue ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PKT_DATA_SUBTITLE_POSITION ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_bprint_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  av_bprintf (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/ * av_packet_new_side_data (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ff_subtitles_queue_insert (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_event(FFDemuxSubtitlesQueue *q, AVBPrint *buf, char *line_cache,
                     const struct event_info *ei, int append_cache)
{
    if (append_cache && line_cache[0])
        av_bprintf(buf, "%s\n", line_cache);
    line_cache[0] = 0;

    while (buf->len > 0 && buf->str[buf->len - 1] == '\n')
        buf->str[--buf->len] = 0;

    if (buf->len) {
        AVPacket *sub = ff_subtitles_queue_insert(q, buf->str, buf->len, 0);
        if (!sub)
            return AVERROR(ENOMEM);
        av_bprint_clear(buf);
        sub->pos = ei->pos;
        sub->pts = ei->pts;
        sub->duration = ei->duration;
        if (ei->x1 != -1) {
            uint8_t *p = av_packet_new_side_data(sub, AV_PKT_DATA_SUBTITLE_POSITION, 16);
            if (p) {
                AV_WL32(p,      ei->x1);
                AV_WL32(p +  4, ei->y1);
                AV_WL32(p +  8, ei->x2);
                AV_WL32(p + 12, ei->y2);
            }
        }
    }

    return 0;
}