#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  status; TYPE_2__ buf; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ V4L2Buffer ;
struct TYPE_8__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2BUF_IN_DRIVER ; 
 int /*<<< orphan*/  VIDIOC_QBUF ; 
 TYPE_4__* buf_to_m2mctx (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

int ff_v4l2_buffer_enqueue(V4L2Buffer* avbuf)
{
    int ret;

    avbuf->buf.flags = avbuf->flags;

    ret = ioctl(buf_to_m2mctx(avbuf)->fd, VIDIOC_QBUF, &avbuf->buf);
    if (ret < 0)
        return AVERROR(errno);

    avbuf->status = V4L2BUF_IN_DRIVER;

    return 0;
}