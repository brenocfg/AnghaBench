#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  context_ref; TYPE_2__* context; } ;
typedef  TYPE_1__ V4L2m2mPriv ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/ * self_ref; TYPE_4__ output; TYPE_4__ capture; } ;
typedef  TYPE_2__ V4L2m2mContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  VIDIOC_STREAMOFF ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_v4l2_context_release (TYPE_4__*) ; 
 int ff_v4l2_context_set_status (TYPE_4__*,int /*<<< orphan*/ ) ; 

int ff_v4l2_m2m_codec_end(V4L2m2mPriv *priv)
{
    V4L2m2mContext* s = priv->context;
    int ret;

    ret = ff_v4l2_context_set_status(&s->output, VIDIOC_STREAMOFF);
    if (ret)
        av_log(priv, AV_LOG_ERROR, "VIDIOC_STREAMOFF %s\n", s->output.name);

    ret = ff_v4l2_context_set_status(&s->capture, VIDIOC_STREAMOFF);
    if (ret)
        av_log(priv, AV_LOG_ERROR, "VIDIOC_STREAMOFF %s\n", s->capture.name);

    ff_v4l2_context_release(&s->output);

    s->self_ref = NULL;
    av_buffer_unref(&priv->context_ref);

    return 0;
}