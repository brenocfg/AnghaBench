#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  refcount; int /*<<< orphan*/  self_ref; } ;
typedef  TYPE_3__ V4L2m2mContext ;
struct TYPE_12__ {int num_planes; int context_refcount; int /*<<< orphan*/  status; int /*<<< orphan*/  context_ref; TYPE_2__* plane_info; TYPE_1__* planes; } ;
typedef  TYPE_4__ V4L2Buffer ;
struct TYPE_10__ {int /*<<< orphan*/  length; scalar_t__ mm_addr; } ;
struct TYPE_9__ {int data_offset; } ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  V4L2BUF_RET_USER ; 
 int /*<<< orphan*/  atomic_fetch_add (int*,int) ; 
 int /*<<< orphan*/  atomic_fetch_add_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_buffer_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffer_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ **) ; 
 TYPE_3__* buf_to_m2mctx (TYPE_4__*) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 
 int /*<<< orphan*/  v4l2_free_buffer ; 

__attribute__((used)) static int v4l2_buf_to_bufref(V4L2Buffer *in, int plane, AVBufferRef **buf)
{
    V4L2m2mContext *s = buf_to_m2mctx(in);

    if (plane >= in->num_planes)
        return AVERROR(EINVAL);

    /* even though most encoders return 0 in data_offset encoding vp8 does require this value */
    *buf = av_buffer_create((char *)in->plane_info[plane].mm_addr + in->planes[plane].data_offset,
                            in->plane_info[plane].length, v4l2_free_buffer, in, 0);
    if (!*buf)
        return AVERROR(ENOMEM);

    if (in->context_ref)
        atomic_fetch_add(&in->context_refcount, 1);
    else {
        in->context_ref = av_buffer_ref(s->self_ref);
        if (!in->context_ref) {
            av_buffer_unref(buf);
            return AVERROR(ENOMEM);
        }
        in->context_refcount = 1;
    }

    in->status = V4L2BUF_RET_USER;
    atomic_fetch_add_explicit(&s->refcount, 1, memory_order_relaxed);

    return 0;
}