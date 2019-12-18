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
struct TYPE_6__ {scalar_t__ duration; scalar_t__ pts; } ;
struct TYPE_5__ {int nb_subs; scalar_t__ sort; int /*<<< orphan*/  keep_duplicates; TYPE_2__* subs; } ;
typedef  TYPE_1__ FFDemuxSubtitlesQueue ;

/* Variables and functions */
 scalar_t__ SUB_SORT_TS_POS ; 
 int /*<<< orphan*/  cmp_pkt_sub_pos_ts ; 
 int /*<<< orphan*/  cmp_pkt_sub_ts_pos ; 
 int /*<<< orphan*/  drop_dups (void*,TYPE_1__*) ; 
 int /*<<< orphan*/  qsort (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 

void ff_subtitles_queue_finalize(void *log_ctx, FFDemuxSubtitlesQueue *q)
{
    int i;

    if (!q->nb_subs)
        return;

    qsort(q->subs, q->nb_subs, sizeof(*q->subs),
          q->sort == SUB_SORT_TS_POS ? cmp_pkt_sub_ts_pos
                                     : cmp_pkt_sub_pos_ts);
    for (i = 0; i < q->nb_subs; i++)
        if (q->subs[i].duration < 0 && i < q->nb_subs - 1)
            q->subs[i].duration = q->subs[i + 1].pts - q->subs[i].pts;

    if (!q->keep_duplicates)
        drop_dups(log_ctx, q);
}