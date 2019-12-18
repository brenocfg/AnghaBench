#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  refcount; int /*<<< orphan*/  self_ref; } ;
typedef  TYPE_1__ V4L2m2mContext ;
struct TYPE_7__ {int context_refcount; int /*<<< orphan*/  status; int /*<<< orphan*/  context_ref; } ;
typedef  TYPE_2__ V4L2Buffer ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  V4L2BUF_RET_USER ; 
 int /*<<< orphan*/  atomic_fetch_add (int*,int) ; 
 int /*<<< orphan*/  atomic_fetch_add_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffer_ref (int /*<<< orphan*/ ) ; 
 TYPE_1__* buf_to_m2mctx (TYPE_2__*) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 

__attribute__((used)) static int v4l2_buf_increase_ref(V4L2Buffer *in)
{
    V4L2m2mContext *s = buf_to_m2mctx(in);

    if (in->context_ref)
        atomic_fetch_add(&in->context_refcount, 1);
    else {
        in->context_ref = av_buffer_ref(s->self_ref);
        if (!in->context_ref)
            return AVERROR(ENOMEM);

        in->context_refcount = 1;
    }

    in->status = V4L2BUF_RET_USER;
    atomic_fetch_add_explicit(&s->refcount, 1, memory_order_relaxed);

    return 0;
}