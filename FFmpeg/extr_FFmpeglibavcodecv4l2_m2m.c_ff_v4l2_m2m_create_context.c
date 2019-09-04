#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {scalar_t__ context_ref; TYPE_4__* context; int /*<<< orphan*/  num_output_buffers; int /*<<< orphan*/  num_capture_buffers; } ;
typedef  TYPE_3__ V4L2m2mPriv ;
struct TYPE_11__ {int /*<<< orphan*/  num_buffers; } ;
struct TYPE_10__ {int /*<<< orphan*/  num_buffers; } ;
struct TYPE_13__ {scalar_t__ self_ref; TYPE_2__ output; TYPE_1__ capture; } ;
typedef  TYPE_4__ V4L2m2mContext ;
struct TYPE_14__ {TYPE_3__* priv_data; } ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ av_buffer_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (TYPE_4__**) ; 
 TYPE_4__* av_mallocz (int) ; 
 int /*<<< orphan*/  v4l2_m2m_destroy_context ; 

int ff_v4l2_m2m_create_context(AVCodecContext *avctx, V4L2m2mContext **s)
{
    V4L2m2mPriv *priv = avctx->priv_data;

    *s = av_mallocz(sizeof(V4L2m2mContext));
    if (!*s)
        return AVERROR(ENOMEM);

    priv->context_ref = av_buffer_create((uint8_t *) *s, sizeof(V4L2m2mContext),
                                         &v4l2_m2m_destroy_context, NULL, 0);
    if (!priv->context_ref) {
        av_freep(s);
        return AVERROR(ENOMEM);
    }

    /* assign the context */
    priv->context = *s;

    /* populate it */
    priv->context->capture.num_buffers = priv->num_capture_buffers;
    priv->context->output.num_buffers  = priv->num_output_buffers;
    priv->context->self_ref = priv->context_ref;

    return 0;
}