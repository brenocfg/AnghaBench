#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_14__ {TYPE_1__* avctx; } ;
typedef  TYPE_4__ V4L2m2mContext ;
struct TYPE_12__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_13__ {TYPE_2__ timestamp; } ;
struct TYPE_15__ {TYPE_3__ buf; } ;
typedef  TYPE_5__ V4L2Buffer ;
struct TYPE_16__ {int member_0; scalar_t__ member_1; } ;
struct TYPE_11__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_6__ AVRational ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ USEC_PER_SEC ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,TYPE_6__) ; 
 TYPE_4__* buf_to_m2mctx (TYPE_5__*) ; 

__attribute__((used)) static inline void v4l2_set_pts(V4L2Buffer *out, int64_t pts)
{
    V4L2m2mContext *s = buf_to_m2mctx(out);
    AVRational v4l2_timebase = { 1, USEC_PER_SEC };
    int64_t v4l2_pts;

    if (pts == AV_NOPTS_VALUE)
        pts = 0;

    /* convert pts to v4l2 timebase */
    v4l2_pts = av_rescale_q(pts, s->avctx->time_base, v4l2_timebase);
    out->buf.timestamp.tv_usec = v4l2_pts % USEC_PER_SEC;
    out->buf.timestamp.tv_sec = v4l2_pts / USEC_PER_SEC;
}