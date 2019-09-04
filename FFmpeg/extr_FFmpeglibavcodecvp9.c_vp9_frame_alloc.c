#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VP9mvrefPair ;
struct TYPE_14__ {TYPE_2__* hwaccel_priv_buf; scalar_t__ hwaccel_picture_private; TYPE_1__* extradata; int /*<<< orphan*/ * mv; scalar_t__ segmentation_map; int /*<<< orphan*/  tf; } ;
typedef  TYPE_3__ VP9Frame ;
struct TYPE_15__ {int sb_cols; int sb_rows; } ;
typedef  TYPE_4__ VP9Context ;
struct TYPE_17__ {TYPE_5__* hwaccel; TYPE_4__* priv_data; } ;
struct TYPE_16__ {int frame_priv_data_size; } ;
struct TYPE_13__ {scalar_t__ data; } ;
struct TYPE_12__ {scalar_t__ data; } ;
typedef  TYPE_5__ AVHWAccel ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 void* av_buffer_allocz (int) ; 
 int ff_thread_get_buffer (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vp9_frame_unref (TYPE_6__*,TYPE_3__*) ; 

__attribute__((used)) static int vp9_frame_alloc(AVCodecContext *avctx, VP9Frame *f)
{
    VP9Context *s = avctx->priv_data;
    int ret, sz;

    ret = ff_thread_get_buffer(avctx, &f->tf, AV_GET_BUFFER_FLAG_REF);
    if (ret < 0)
        return ret;

    sz = 64 * s->sb_cols * s->sb_rows;
    f->extradata = av_buffer_allocz(sz * (1 + sizeof(VP9mvrefPair)));
    if (!f->extradata) {
        goto fail;
    }

    f->segmentation_map = f->extradata->data;
    f->mv = (VP9mvrefPair *) (f->extradata->data + sz);

    if (avctx->hwaccel) {
        const AVHWAccel *hwaccel = avctx->hwaccel;
        av_assert0(!f->hwaccel_picture_private);
        if (hwaccel->frame_priv_data_size) {
            f->hwaccel_priv_buf = av_buffer_allocz(hwaccel->frame_priv_data_size);
            if (!f->hwaccel_priv_buf)
                goto fail;
            f->hwaccel_picture_private = f->hwaccel_priv_buf->data;
        }
    }

    return 0;

fail:
    vp9_frame_unref(avctx, f);
    return AVERROR(ENOMEM);
}