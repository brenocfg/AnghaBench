#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_23__ {size_t subsampling_x; size_t subsampling_y; int /*<<< orphan*/  mono_chrome; } ;
struct TYPE_34__ {int /*<<< orphan*/ * seq_level_idx; int /*<<< orphan*/  seq_profile; TYPE_12__ color_config; } ;
struct TYPE_33__ {int frame_type; int /*<<< orphan*/  frame_height; int /*<<< orphan*/  frame_width; int /*<<< orphan*/  valid; } ;
struct TYPE_32__ {int extradata_size; int /*<<< orphan*/  level; int /*<<< orphan*/  profile; int /*<<< orphan*/  const* extradata; } ;
struct TYPE_31__ {int key_frame; scalar_t__ format; int /*<<< orphan*/  picture_structure; int /*<<< orphan*/  pict_type; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_13__* priv_data; } ;
struct TYPE_30__ {int bit_depth; int /*<<< orphan*/  frame_height; int /*<<< orphan*/  frame_width; TYPE_8__* ref; TYPE_9__* sequence_header; } ;
struct TYPE_29__ {int nb_units; TYPE_3__* units; } ;
struct TYPE_28__ {scalar_t__ type; TYPE_10__* content; } ;
struct TYPE_22__ {size_t frame_to_show_map_idx; int frame_type; int /*<<< orphan*/  show_frame; scalar_t__ show_existing_frame; } ;
struct TYPE_26__ {TYPE_11__ header; } ;
struct TYPE_27__ {TYPE_11__ frame_header; TYPE_1__ frame; } ;
struct TYPE_25__ {TYPE_7__* log_ctx; TYPE_5__* priv_data; } ;
struct TYPE_24__ {int parsed_extradata; TYPE_14__* cbc; TYPE_4__ temporal_unit; } ;
struct TYPE_21__ {TYPE_2__ obu; } ;
typedef  TYPE_3__ CodedBitstreamUnit ;
typedef  TYPE_4__ CodedBitstreamFragment ;
typedef  TYPE_5__ CodedBitstreamAV1Context ;
typedef  TYPE_6__ AVCodecParserContext ;
typedef  TYPE_7__ AVCodecContext ;
typedef  TYPE_8__ AV1ReferenceFrameState ;
typedef  TYPE_9__ AV1RawSequenceHeader ;
typedef  TYPE_10__ AV1RawOBU ;
typedef  TYPE_11__ AV1RawFrameHeader ;
typedef  TYPE_12__ AV1RawColorConfig ;
typedef  TYPE_13__ AV1ParseContext ;

/* Variables and functions */
#define  AV1_FRAME_INTER 131 
#define  AV1_FRAME_INTRA_ONLY 130 
#define  AV1_FRAME_KEY 129 
#define  AV1_FRAME_SWITCH 128 
 scalar_t__ AV1_OBU_FRAME ; 
 scalar_t__ AV1_OBU_FRAME_HEADER ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PICTURE_STRUCTURE_FRAME ; 
 int /*<<< orphan*/  AV_PICTURE_STRUCTURE_UNKNOWN ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_NONE ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_SP ; 
 scalar_t__ AV_PIX_FMT_GRAY10 ; 
 scalar_t__ AV_PIX_FMT_GRAY12 ; 
 scalar_t__ AV_PIX_FMT_GRAY8 ; 
 scalar_t__ AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_cbs_fragment_reset (TYPE_14__*,TYPE_4__*) ; 
 int ff_cbs_read (TYPE_14__*,TYPE_4__*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__** pix_fmts_10bit ; 
 scalar_t__** pix_fmts_12bit ; 
 scalar_t__** pix_fmts_8bit ; 

__attribute__((used)) static int av1_parser_parse(AVCodecParserContext *ctx,
                            AVCodecContext *avctx,
                            const uint8_t **out_data, int *out_size,
                            const uint8_t *data, int size)
{
    AV1ParseContext *s = ctx->priv_data;
    CodedBitstreamFragment *td = &s->temporal_unit;
    CodedBitstreamAV1Context *av1 = s->cbc->priv_data;
    int ret;

    *out_data = data;
    *out_size = size;

    ctx->key_frame         = -1;
    ctx->pict_type         = AV_PICTURE_TYPE_NONE;
    ctx->picture_structure = AV_PICTURE_STRUCTURE_UNKNOWN;

    s->cbc->log_ctx = avctx;

    if (avctx->extradata_size && !s->parsed_extradata) {
        s->parsed_extradata = 1;

        ret = ff_cbs_read(s->cbc, td, avctx->extradata, avctx->extradata_size);
        if (ret < 0) {
            av_log(avctx, AV_LOG_WARNING, "Failed to parse extradata.\n");
        }

        ff_cbs_fragment_reset(s->cbc, td);
    }

    ret = ff_cbs_read(s->cbc, td, data, size);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "Failed to parse temporal unit.\n");
        goto end;
    }

    if (!av1->sequence_header) {
        av_log(avctx, AV_LOG_ERROR, "No sequence header available\n");
        goto end;
    }

    for (int i = 0; i < td->nb_units; i++) {
        CodedBitstreamUnit *unit = &td->units[i];
        AV1RawOBU *obu = unit->content;
        AV1RawSequenceHeader *seq = av1->sequence_header;
        AV1RawColorConfig *color = &seq->color_config;
        AV1RawFrameHeader *frame;
        int frame_type;

        if (unit->type == AV1_OBU_FRAME)
            frame = &obu->obu.frame.header;
        else if (unit->type == AV1_OBU_FRAME_HEADER)
            frame = &obu->obu.frame_header;
        else
            continue;

        if (frame->show_existing_frame) {
            AV1ReferenceFrameState *ref = &av1->ref[frame->frame_to_show_map_idx];

            if (!ref->valid) {
                av_log(avctx, AV_LOG_ERROR, "Invalid reference frame\n");
                goto end;
            }

            ctx->width  = ref->frame_width;
            ctx->height = ref->frame_height;
            frame_type  = ref->frame_type;

            ctx->key_frame = 0;
        } else if (!frame->show_frame) {
            continue;
        } else {
            ctx->width  = av1->frame_width;
            ctx->height = av1->frame_height;
            frame_type  = frame->frame_type;

            ctx->key_frame = frame_type == AV1_FRAME_KEY;
        }

        avctx->profile = seq->seq_profile;
        avctx->level   = seq->seq_level_idx[0];

        switch (frame_type) {
        case AV1_FRAME_KEY:
        case AV1_FRAME_INTRA_ONLY:
            ctx->pict_type = AV_PICTURE_TYPE_I;
            break;
        case AV1_FRAME_INTER:
            ctx->pict_type = AV_PICTURE_TYPE_P;
            break;
        case AV1_FRAME_SWITCH:
            ctx->pict_type = AV_PICTURE_TYPE_SP;
            break;
        }
        ctx->picture_structure = AV_PICTURE_STRUCTURE_FRAME;

        switch (av1->bit_depth) {
        case 8:
            ctx->format = color->mono_chrome ? AV_PIX_FMT_GRAY8
                                             : pix_fmts_8bit [color->subsampling_x][color->subsampling_y];
            break;
        case 10:
            ctx->format = color->mono_chrome ? AV_PIX_FMT_GRAY10
                                             : pix_fmts_10bit[color->subsampling_x][color->subsampling_y];
            break;
        case 12:
            ctx->format = color->mono_chrome ? AV_PIX_FMT_GRAY12
                                             : pix_fmts_12bit[color->subsampling_x][color->subsampling_y];
            break;
        }
        av_assert2(ctx->format != AV_PIX_FMT_NONE);
    }

end:
    ff_cbs_fragment_reset(s->cbc, td);

    s->cbc->log_ctx = NULL;

    return size;
}