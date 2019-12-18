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
struct TYPE_9__ {TYPE_3__* work_frames; } ;
struct TYPE_6__ {int /*<<< orphan*/  Locked; } ;
struct TYPE_7__ {TYPE_1__ Data; } ;
struct TYPE_8__ {struct TYPE_8__* next; int /*<<< orphan*/  frame; scalar_t__ used; int /*<<< orphan*/  queued; TYPE_2__ surface; } ;
typedef  TYPE_3__ QSVFrame ;
typedef  TYPE_4__ QSVContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qsv_clear_unused_frames(QSVContext *q)
{
    QSVFrame *cur = q->work_frames;
    while (cur) {
        if (cur->used && !cur->surface.Data.Locked && !cur->queued) {
            cur->used = 0;
            av_frame_unref(cur->frame);
        }
        cur = cur->next;
    }
}