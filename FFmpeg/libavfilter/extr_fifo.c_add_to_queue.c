#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * frame; struct TYPE_9__* next; } ;
struct TYPE_8__ {TYPE_1__* dst; } ;
struct TYPE_7__ {TYPE_4__* last; } ;
struct TYPE_6__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ FifoContext ;
typedef  int /*<<< orphan*/  Buf ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 TYPE_4__* av_mallocz (int) ; 

__attribute__((used)) static int add_to_queue(AVFilterLink *inlink, AVFrame *frame)
{
    FifoContext *s = inlink->dst->priv;

    s->last->next = av_mallocz(sizeof(Buf));
    if (!s->last->next) {
        av_frame_free(&frame);
        return AVERROR(ENOMEM);
    }

    s->last = s->last->next;
    s->last->frame = frame;

    return 0;
}