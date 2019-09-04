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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {scalar_t__ draining; int /*<<< orphan*/  refsync; int /*<<< orphan*/  refcount; scalar_t__ reinit; } ;
typedef  TYPE_2__ V4L2m2mContext ;
struct TYPE_9__ {int /*<<< orphan*/  context_ref; TYPE_1__* context; int /*<<< orphan*/  status; int /*<<< orphan*/  context_refcount; } ;
typedef  TYPE_3__ V4L2Buffer ;
struct TYPE_7__ {scalar_t__ streamon; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2BUF_AVAILABLE ; 
 int atomic_fetch_sub (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_fetch_sub_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 TYPE_2__* buf_to_m2mctx (TYPE_3__*) ; 
 int /*<<< orphan*/  ff_v4l2_buffer_enqueue (TYPE_3__*) ; 
 int /*<<< orphan*/  memory_order_acq_rel ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void v4l2_free_buffer(void *opaque, uint8_t *unused)
{
    V4L2Buffer* avbuf = opaque;
    V4L2m2mContext *s = buf_to_m2mctx(avbuf);

    if (atomic_fetch_sub(&avbuf->context_refcount, 1) == 1) {
        atomic_fetch_sub_explicit(&s->refcount, 1, memory_order_acq_rel);

        if (s->reinit) {
            if (!atomic_load(&s->refcount))
                sem_post(&s->refsync);
        } else {
            if (s->draining) {
                /* no need to queue more buffers to the driver */
                avbuf->status = V4L2BUF_AVAILABLE;
            }
            else if (avbuf->context->streamon)
                ff_v4l2_buffer_enqueue(avbuf);
        }

        av_buffer_unref(&avbuf->context_ref);
    }
}