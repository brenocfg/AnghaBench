#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int num_planes; } ;
typedef  TYPE_1__ V4L2Buffer ;
struct TYPE_10__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int /*<<< orphan*/  pts; TYPE_5__** buf; } ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int v4l2_bufref_to_buf (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  v4l2_set_pts (TYPE_1__*,int /*<<< orphan*/ ) ; 

int ff_v4l2_buffer_avframe_to_buf(const AVFrame *frame, V4L2Buffer* out)
{
    int i, ret;

    for(i = 0; i < out->num_planes; i++) {
        ret = v4l2_bufref_to_buf(out, i, frame->buf[i]->data, frame->buf[i]->size, frame->buf[i]);
        if (ret)
            return ret;
    }

    v4l2_set_pts(out, frame->pts);

    return 0;
}