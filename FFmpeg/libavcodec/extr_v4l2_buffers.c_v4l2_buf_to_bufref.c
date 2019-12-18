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
struct TYPE_9__ {int num_planes; TYPE_2__* plane_info; TYPE_1__* planes; } ;
typedef  TYPE_3__ V4L2Buffer ;
struct TYPE_8__ {int /*<<< orphan*/  length; scalar_t__ mm_addr; } ;
struct TYPE_7__ {int data_offset; } ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_buffer_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ **) ; 
 int v4l2_buf_increase_ref (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_free_buffer ; 

__attribute__((used)) static int v4l2_buf_to_bufref(V4L2Buffer *in, int plane, AVBufferRef **buf)
{
    int ret;

    if (plane >= in->num_planes)
        return AVERROR(EINVAL);

    /* even though most encoders return 0 in data_offset encoding vp8 does require this value */
    *buf = av_buffer_create((char *)in->plane_info[plane].mm_addr + in->planes[plane].data_offset,
                            in->plane_info[plane].length, v4l2_free_buffer, in, 0);
    if (!*buf)
        return AVERROR(ENOMEM);

    ret = v4l2_buf_increase_ref(in);
    if (ret)
        av_buffer_unref(buf);

    return ret;
}