#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ V4L2Context ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 

__attribute__((used)) static inline int v4l2_type_supported(V4L2Context *ctx)
{
    return ctx->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ||
        ctx->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ||
        ctx->type == V4L2_BUF_TYPE_VIDEO_CAPTURE ||
        ctx->type == V4L2_BUF_TYPE_VIDEO_OUTPUT;
}