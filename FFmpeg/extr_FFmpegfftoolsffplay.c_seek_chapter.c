#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_8__ {TYPE_1__* ic; } ;
typedef  TYPE_2__ VideoState ;
struct TYPE_9__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  start; } ;
struct TYPE_7__ {int nb_chapters; TYPE_3__** chapters; } ;
typedef  TYPE_3__ AVChapter ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int AV_TIME_BASE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 scalar_t__ av_compare_ts (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_master_clock (TYPE_2__*) ; 
 int /*<<< orphan*/  stream_seek (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void seek_chapter(VideoState *is, int incr)
{
    int64_t pos = get_master_clock(is) * AV_TIME_BASE;
    int i;

    if (!is->ic->nb_chapters)
        return;

    /* find the current chapter */
    for (i = 0; i < is->ic->nb_chapters; i++) {
        AVChapter *ch = is->ic->chapters[i];
        if (av_compare_ts(pos, AV_TIME_BASE_Q, ch->start, ch->time_base) < 0) {
            i--;
            break;
        }
    }

    i += incr;
    i = FFMAX(i, 0);
    if (i >= is->ic->nb_chapters)
        return;

    av_log(NULL, AV_LOG_VERBOSE, "Seeking to chapter %d.\n", i);
    stream_seek(is, av_rescale_q(is->ic->chapters[i]->start, is->ic->chapters[i]->time_base,
                                 AV_TIME_BASE_Q), 0, 0);
}