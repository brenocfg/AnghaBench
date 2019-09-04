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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int int64_t ;
struct TYPE_14__ {TYPE_3__* avctx; } ;
typedef  TYPE_4__ V4L2m2mContext ;
struct TYPE_11__ {int tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_12__ {TYPE_1__ timestamp; } ;
struct TYPE_15__ {TYPE_2__ buf; } ;
typedef  TYPE_5__ V4L2Buffer ;
struct TYPE_16__ {int member_0; int member_1; } ;
struct TYPE_13__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_6__ AVRational ;

/* Variables and functions */
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  av_rescale_q (int,TYPE_6__,int /*<<< orphan*/ ) ; 
 TYPE_4__* buf_to_m2mctx (TYPE_5__*) ; 

__attribute__((used)) static inline uint64_t v4l2_get_pts(V4L2Buffer *avbuf)
{
    V4L2m2mContext *s = buf_to_m2mctx(avbuf);
    AVRational v4l2_timebase = { 1, USEC_PER_SEC };
    int64_t v4l2_pts;

    /* convert pts back to encoder timebase */
    v4l2_pts = (int64_t)avbuf->buf.timestamp.tv_sec * USEC_PER_SEC +
                        avbuf->buf.timestamp.tv_usec;

    return av_rescale_q(v4l2_pts, v4l2_timebase, s->avctx->time_base);
}