#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* work_frames; } ;
struct TYPE_7__ {struct TYPE_7__* next; int /*<<< orphan*/  used; } ;
typedef  TYPE_1__ QSVFrame ;
typedef  TYPE_2__ QSVDeintContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_1__* av_mallocz (int) ; 
 int /*<<< orphan*/  clear_unused_frames (TYPE_2__*) ; 

__attribute__((used)) static int get_free_frame(QSVDeintContext *s, QSVFrame **f)
{
    QSVFrame *frame, **last;

    clear_unused_frames(s);

    frame = s->work_frames;
    last  = &s->work_frames;
    while (frame) {
        if (!frame->used) {
            *f = frame;
            return 0;
        }

        last  = &frame->next;
        frame = frame->next;
    }

    frame = av_mallocz(sizeof(*frame));
    if (!frame)
        return AVERROR(ENOMEM);
    *last = frame;
    *f    = frame;

    return 0;
}