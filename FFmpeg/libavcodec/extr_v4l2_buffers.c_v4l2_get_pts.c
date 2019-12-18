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
typedef  int int64_t ;
struct TYPE_6__ {int tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_7__ {TYPE_1__ timestamp; } ;
struct TYPE_8__ {TYPE_2__ buf; } ;
typedef  TYPE_3__ V4L2Buffer ;

/* Variables and functions */
 int USEC_PER_SEC ; 
 int av_rescale_q (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_get_timebase (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_timebase ; 

__attribute__((used)) static inline int64_t v4l2_get_pts(V4L2Buffer *avbuf)
{
    int64_t v4l2_pts;

    /* convert pts back to encoder timebase */
    v4l2_pts = (int64_t)avbuf->buf.timestamp.tv_sec * USEC_PER_SEC +
                        avbuf->buf.timestamp.tv_usec;

    return av_rescale_q(v4l2_pts, v4l2_timebase, v4l2_get_timebase(avbuf));
}