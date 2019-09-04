#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {int err_recognition; int debug; TYPE_4__* priv_data; } ;
struct TYPE_9__ {TYPE_1__* f; } ;
struct TYPE_10__ {int pict_type; int vbv_delay; int** mpeg_f_code; int y_dc_scale; int c_dc_scale; TYPE_2__ current_picture; int /*<<< orphan*/  gb; void** full_pel; } ;
struct TYPE_11__ {TYPE_3__ mpeg_enc_ctx; } ;
struct TYPE_8__ {int pict_type; int key_frame; } ;
typedef  TYPE_3__ MpegEncContext ;
typedef  TYPE_4__ Mpeg1Context ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_EF_BITSTREAM ; 
 int AV_EF_COMPLIANT ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int AV_PICTURE_TYPE_B ; 
 int AV_PICTURE_TYPE_I ; 
 int AV_PICTURE_TYPE_P ; 
 int FF_DEBUG_PICT_INFO ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int mpeg1_decode_picture(AVCodecContext *avctx, const uint8_t *buf,
                                int buf_size)
{
    Mpeg1Context *s1  = avctx->priv_data;
    MpegEncContext *s = &s1->mpeg_enc_ctx;
    int ref, f_code, vbv_delay;

    init_get_bits(&s->gb, buf, buf_size * 8);

    ref = get_bits(&s->gb, 10); /* temporal ref */
    s->pict_type = get_bits(&s->gb, 3);
    if (s->pict_type == 0 || s->pict_type > 3)
        return AVERROR_INVALIDDATA;

    vbv_delay = get_bits(&s->gb, 16);
    s->vbv_delay = vbv_delay;
    if (s->pict_type == AV_PICTURE_TYPE_P ||
        s->pict_type == AV_PICTURE_TYPE_B) {
        s->full_pel[0] = get_bits1(&s->gb);
        f_code = get_bits(&s->gb, 3);
        if (f_code == 0 && (avctx->err_recognition & (AV_EF_BITSTREAM|AV_EF_COMPLIANT)))
            return AVERROR_INVALIDDATA;
        f_code += !f_code;
        s->mpeg_f_code[0][0] = f_code;
        s->mpeg_f_code[0][1] = f_code;
    }
    if (s->pict_type == AV_PICTURE_TYPE_B) {
        s->full_pel[1] = get_bits1(&s->gb);
        f_code = get_bits(&s->gb, 3);
        if (f_code == 0 && (avctx->err_recognition & (AV_EF_BITSTREAM|AV_EF_COMPLIANT)))
            return AVERROR_INVALIDDATA;
        f_code += !f_code;
        s->mpeg_f_code[1][0] = f_code;
        s->mpeg_f_code[1][1] = f_code;
    }
    s->current_picture.f->pict_type = s->pict_type;
    s->current_picture.f->key_frame = s->pict_type == AV_PICTURE_TYPE_I;

    if (avctx->debug & FF_DEBUG_PICT_INFO)
        av_log(avctx, AV_LOG_DEBUG,
               "vbv_delay %d, ref %d type:%d\n", vbv_delay, ref, s->pict_type);

    s->y_dc_scale = 8;
    s->c_dc_scale = 8;
    return 0;
}