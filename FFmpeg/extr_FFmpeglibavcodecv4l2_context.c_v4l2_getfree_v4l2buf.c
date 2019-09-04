#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int num_buffers; TYPE_2__* buffers; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ V4L2Context ;
struct TYPE_7__ {scalar_t__ status; } ;
typedef  TYPE_2__ V4L2Buffer ;

/* Variables and functions */
 scalar_t__ V4L2BUF_AVAILABLE ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 scalar_t__ v4l2_dequeue_v4l2buf (TYPE_1__*,int) ; 

__attribute__((used)) static V4L2Buffer* v4l2_getfree_v4l2buf(V4L2Context *ctx)
{
    int timeout = 0; /* return when no more buffers to dequeue */
    int i;

    /* get back as many output buffers as possible */
    if (V4L2_TYPE_IS_OUTPUT(ctx->type)) {
          do {
          } while (v4l2_dequeue_v4l2buf(ctx, timeout));
    }

    for (i = 0; i < ctx->num_buffers; i++) {
        if (ctx->buffers[i].status == V4L2BUF_AVAILABLE)
            return &ctx->buffers[i];
    }

    return NULL;
}