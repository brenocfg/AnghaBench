#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_7__ {scalar_t__ serial; int pos; } ;
struct TYPE_6__ {size_t rindex; TYPE_1__* pktq; scalar_t__ rindex_shown; TYPE_3__* queue; } ;
struct TYPE_5__ {scalar_t__ serial; } ;
typedef  TYPE_2__ FrameQueue ;
typedef  TYPE_3__ Frame ;

/* Variables and functions */

__attribute__((used)) static int64_t frame_queue_last_pos(FrameQueue *f)
{
    Frame *fp = &f->queue[f->rindex];
    if (f->rindex_shown && fp->serial == f->pktq->serial)
        return fp->pos;
    else
        return -1;
}