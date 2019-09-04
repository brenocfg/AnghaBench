#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* context; } ;
typedef  TYPE_1__ V4L2m2mPriv ;
struct TYPE_6__ {int /*<<< orphan*/  output; } ;
typedef  TYPE_2__ V4L2m2mContext ;
typedef  int /*<<< orphan*/  V4L2Context ;
struct TYPE_7__ {scalar_t__ priv_data; } ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int ff_v4l2_context_enqueue_frame (int /*<<< orphan*/ * const,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int v4l2_send_frame(AVCodecContext *avctx, const AVFrame *frame)
{
    V4L2m2mContext *s = ((V4L2m2mPriv*)avctx->priv_data)->context;
    V4L2Context *const output = &s->output;

    return ff_v4l2_context_enqueue_frame(output, frame);
}