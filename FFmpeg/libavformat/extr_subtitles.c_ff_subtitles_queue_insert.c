#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int size; scalar_t__ data; scalar_t__ dts; scalar_t__ pts; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {scalar_t__ nb_subs; TYPE_2__* subs; int /*<<< orphan*/  allocated_size; } ;
typedef  TYPE_1__ FFDemuxSubtitlesQueue ;
typedef  TYPE_2__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int INT_MAX ; 
 TYPE_2__* av_fast_realloc (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ av_grow_packet (TYPE_2__*,size_t) ; 
 scalar_t__ av_new_packet (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 

AVPacket *ff_subtitles_queue_insert(FFDemuxSubtitlesQueue *q,
                                    const uint8_t *event, size_t len, int merge)
{
    AVPacket *subs, *sub;

    if (merge && q->nb_subs > 0) {
        /* merge with previous event */

        int old_len;
        sub = &q->subs[q->nb_subs - 1];
        old_len = sub->size;
        if (av_grow_packet(sub, len) < 0)
            return NULL;
        memcpy(sub->data + old_len, event, len);
    } else {
        /* new event */

        if (q->nb_subs >= INT_MAX/sizeof(*q->subs) - 1)
            return NULL;
        subs = av_fast_realloc(q->subs, &q->allocated_size,
                               (q->nb_subs + 1) * sizeof(*q->subs));
        if (!subs)
            return NULL;
        q->subs = subs;
        sub = &subs[q->nb_subs++];
        if (av_new_packet(sub, len) < 0)
            return NULL;
        sub->flags |= AV_PKT_FLAG_KEY;
        sub->pts = sub->dts = 0;
        memcpy(sub->data, event, len);
    }
    return sub;
}