#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_1__* f; } ;
struct TYPE_14__ {int /*<<< orphan*/  encoding_error; int /*<<< orphan*/  shared; int /*<<< orphan*/  reference; int /*<<< orphan*/  needs_realloc; int /*<<< orphan*/  b_frame_score; int /*<<< orphan*/  mc_mb_var_sum; int /*<<< orphan*/  mb_var_sum; int /*<<< orphan*/  field_picture; TYPE_10__* hwaccel_priv_buf; scalar_t__ hwaccel_picture_private; TYPE_5__ tf; TYPE_1__* f; } ;
struct TYPE_13__ {int* buf; } ;
struct TYPE_12__ {scalar_t__ data; } ;
typedef  TYPE_2__ Picture ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 TYPE_10__* av_buffer_ref (TYPE_10__*) ; 
 int /*<<< orphan*/  ff_mpeg_unref_picture (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int ff_thread_ref_frame (TYPE_5__*,TYPE_5__*) ; 
 int ff_update_picture_tables (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ff_mpeg_ref_picture(AVCodecContext *avctx, Picture *dst, Picture *src)
{
    int ret;

    av_assert0(!dst->f->buf[0]);
    av_assert0(src->f->buf[0]);

    src->tf.f = src->f;
    dst->tf.f = dst->f;
    ret = ff_thread_ref_frame(&dst->tf, &src->tf);
    if (ret < 0)
        goto fail;

    ret = ff_update_picture_tables(dst, src);
    if (ret < 0)
        goto fail;

    if (src->hwaccel_picture_private) {
        dst->hwaccel_priv_buf = av_buffer_ref(src->hwaccel_priv_buf);
        if (!dst->hwaccel_priv_buf) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        dst->hwaccel_picture_private = dst->hwaccel_priv_buf->data;
    }

    dst->field_picture           = src->field_picture;
    dst->mb_var_sum              = src->mb_var_sum;
    dst->mc_mb_var_sum           = src->mc_mb_var_sum;
    dst->b_frame_score           = src->b_frame_score;
    dst->needs_realloc           = src->needs_realloc;
    dst->reference               = src->reference;
    dst->shared                  = src->shared;

    memcpy(dst->encoding_error, src->encoding_error,
           sizeof(dst->encoding_error));

    return 0;
fail:
    ff_mpeg_unref_picture(avctx, dst);
    return ret;
}