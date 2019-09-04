#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nb_subs; int allocated_size; int current_sub_idx; int /*<<< orphan*/ * subs; } ;
typedef  TYPE_1__ FFDemuxSubtitlesQueue ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 

void ff_subtitles_queue_clean(FFDemuxSubtitlesQueue *q)
{
    int i;

    for (i = 0; i < q->nb_subs; i++)
        av_packet_unref(&q->subs[i]);
    av_freep(&q->subs);
    q->nb_subs = q->allocated_size = q->current_sub_idx = 0;
}