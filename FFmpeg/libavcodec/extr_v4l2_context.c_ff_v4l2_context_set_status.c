#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int type; int streamon; } ;
typedef  TYPE_1__ V4L2Context ;
struct TYPE_6__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ VIDIOC_STREAMON ; 
 TYPE_3__* ctx_to_m2mctx (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,scalar_t__,int*) ; 

int ff_v4l2_context_set_status(V4L2Context* ctx, uint32_t cmd)
{
    int type = ctx->type;
    int ret;

    ret = ioctl(ctx_to_m2mctx(ctx)->fd, cmd, &type);
    if (ret < 0)
        return AVERROR(errno);

    ctx->streamon = (cmd == VIDIOC_STREAMON);

    return 0;
}