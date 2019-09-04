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
struct TYPE_5__ {int /*<<< orphan*/  intra_period; int /*<<< orphan*/  bits_per_second; scalar_t__ kf_auto; scalar_t__ error_resilient; scalar_t__ frame_height_scale; scalar_t__ frame_width_scale; int /*<<< orphan*/  frame_height; int /*<<< orphan*/  frame_width; } ;
typedef  TYPE_1__ VAEncSequenceParameterBufferVP8 ;
struct TYPE_6__ {int va_rc_mode; int /*<<< orphan*/  gop_size; int /*<<< orphan*/  va_bit_rate; TYPE_1__* codec_sequence_params; } ;
typedef  TYPE_2__ VAAPIEncodeContext ;
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_2__* priv_data; } ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int VA_RC_CQP ; 

__attribute__((used)) static int vaapi_encode_vp8_init_sequence_params(AVCodecContext *avctx)
{
    VAAPIEncodeContext               *ctx = avctx->priv_data;
    VAEncSequenceParameterBufferVP8 *vseq = ctx->codec_sequence_params;

    vseq->frame_width  = avctx->width;
    vseq->frame_height = avctx->height;

    vseq->frame_width_scale  = 0;
    vseq->frame_height_scale = 0;

    vseq->error_resilient = 0;
    vseq->kf_auto = 0;

    if (!(ctx->va_rc_mode & VA_RC_CQP)) {
        vseq->bits_per_second = ctx->va_bit_rate;
        vseq->intra_period    = ctx->gop_size;
    }

    return 0;
}