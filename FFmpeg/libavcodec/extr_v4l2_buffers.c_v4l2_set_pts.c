#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_7__ {TYPE_1__ timestamp; } ;
struct TYPE_8__ {TYPE_2__ buf; } ;
typedef  TYPE_3__ V4L2Buffer ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ USEC_PER_SEC ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_get_timebase (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_timebase ; 

__attribute__((used)) static inline void v4l2_set_pts(V4L2Buffer *out, int64_t pts)
{
    int64_t v4l2_pts;

    if (pts == AV_NOPTS_VALUE)
        pts = 0;

    /* convert pts to v4l2 timebase */
    v4l2_pts = av_rescale_q(pts, v4l2_get_timebase(out), v4l2_timebase);
    out->buf.timestamp.tv_usec = v4l2_pts % USEC_PER_SEC;
    out->buf.timestamp.tv_sec = v4l2_pts / USEC_PER_SEC;
}