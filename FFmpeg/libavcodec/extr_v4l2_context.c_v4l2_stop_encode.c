#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_encoder_cmd {int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  V4L2Context ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int AVERROR (scalar_t__) ; 
 scalar_t__ ENOTTY ; 
 int /*<<< orphan*/  V4L2_ENC_CMD_STOP ; 
 int /*<<< orphan*/  VIDIOC_ENCODER_CMD ; 
 int /*<<< orphan*/  VIDIOC_STREAMOFF ; 
 TYPE_1__* ctx_to_m2mctx (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int ff_v4l2_context_set_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_encoder_cmd*) ; 

__attribute__((used)) static int v4l2_stop_encode(V4L2Context *ctx)
{
    struct v4l2_encoder_cmd cmd = {
        .cmd = V4L2_ENC_CMD_STOP,
        .flags = 0,
    };
    int ret;

    ret = ioctl(ctx_to_m2mctx(ctx)->fd, VIDIOC_ENCODER_CMD, &cmd);
    if (ret) {
        /* ENCODER_CMD is optional */
        if (errno == ENOTTY)
            return ff_v4l2_context_set_status(ctx, VIDIOC_STREAMOFF);
        else
            return AVERROR(errno);
    }

    return 0;
}