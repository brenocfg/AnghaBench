#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* context; } ;
typedef  TYPE_1__ V4L2m2mPriv ;
struct TYPE_10__ {int /*<<< orphan*/  output; } ;
typedef  TYPE_2__ V4L2m2mContext ;
typedef  int /*<<< orphan*/  V4L2Context ;
struct TYPE_12__ {scalar_t__ priv_data; } ;
struct TYPE_11__ {scalar_t__ pict_type; } ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  FORCE_KEY_FRAME ; 
 int /*<<< orphan*/  MPEG_CID (int /*<<< orphan*/ ) ; 
 int ff_v4l2_context_enqueue_frame (int /*<<< orphan*/ * const,TYPE_3__ const*) ; 
 int /*<<< orphan*/  v4l2_set_ext_ctrl (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int v4l2_send_frame(AVCodecContext *avctx, const AVFrame *frame)
{
    V4L2m2mContext *s = ((V4L2m2mPriv*)avctx->priv_data)->context;
    V4L2Context *const output = &s->output;

#ifdef V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME
    if (frame && frame->pict_type == AV_PICTURE_TYPE_I)
        v4l2_set_ext_ctrl(s, MPEG_CID(FORCE_KEY_FRAME), 0, "force key frame");
#endif

    return ff_v4l2_context_enqueue_frame(output, frame);
}