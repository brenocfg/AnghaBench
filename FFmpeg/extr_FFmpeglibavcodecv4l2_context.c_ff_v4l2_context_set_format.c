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
struct TYPE_5__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ V4L2Context ;
struct TYPE_6__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDIOC_S_FMT ; 
 TYPE_3__* ctx_to_m2mctx (TYPE_1__*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ff_v4l2_context_set_format(V4L2Context* ctx)
{
    return ioctl(ctx_to_m2mctx(ctx)->fd, VIDIOC_S_FMT, &ctx->format);
}