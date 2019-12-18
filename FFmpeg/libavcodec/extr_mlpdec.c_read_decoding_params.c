#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ sample_fmt; } ;
struct TYPE_14__ {scalar_t__ codebook; scalar_t__ huff_lsbs; int /*<<< orphan*/  sign_huff_offset; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* mlp_select_pack_output ) (int /*<<< orphan*/ ,scalar_t__*,unsigned int,int) ;int /*<<< orphan*/  mlp_pack_output; } ;
struct TYPE_13__ {int access_unit_size; unsigned int max_decoded_substream; TYPE_9__* avctx; TYPE_1__ dsp; TYPE_2__* substream; } ;
struct TYPE_12__ {int param_presence_flags; int blocksize; unsigned int max_matrix_channel; scalar_t__* output_shift; unsigned int max_channel; scalar_t__* quant_step_size; unsigned int min_channel; TYPE_4__* channel_params; int /*<<< orphan*/  ch_assign; } ;
typedef  TYPE_2__ SubStream ;
typedef  TYPE_3__ MLPDecodeContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_4__ ChannelParams ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_SAMPLE_FMT_S32 ; 
 int PARAM_BLOCKSIZE ; 
 int PARAM_MATRIX ; 
 int PARAM_OUTSHIFT ; 
 int PARAM_PRESENCE ; 
 int PARAM_QUANTSTEP ; 
 int /*<<< orphan*/  av_log (TYPE_9__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_9__*,char*) ; 
 int /*<<< orphan*/  calculate_sign_huff (TYPE_3__*,unsigned int,unsigned int) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_sbits (int /*<<< orphan*/ *,int) ; 
 int read_channel_params (TYPE_3__*,unsigned int,int /*<<< orphan*/ *,unsigned int) ; 
 int read_matrix_params (TYPE_3__*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__*,unsigned int,int) ; 

__attribute__((used)) static int read_decoding_params(MLPDecodeContext *m, GetBitContext *gbp,
                                unsigned int substr)
{
    SubStream *s = &m->substream[substr];
    unsigned int ch;
    int ret = 0;
    unsigned recompute_sho = 0;

    if (s->param_presence_flags & PARAM_PRESENCE)
        if (get_bits1(gbp))
            s->param_presence_flags = get_bits(gbp, 8);

    if (s->param_presence_flags & PARAM_BLOCKSIZE)
        if (get_bits1(gbp)) {
            s->blocksize = get_bits(gbp, 9);
            if (s->blocksize < 8 || s->blocksize > m->access_unit_size) {
                av_log(m->avctx, AV_LOG_ERROR, "Invalid blocksize.\n");
                s->blocksize = 0;
                return AVERROR_INVALIDDATA;
            }
        }

    if (s->param_presence_flags & PARAM_MATRIX)
        if (get_bits1(gbp))
            if ((ret = read_matrix_params(m, substr, gbp)) < 0)
                return ret;

    if (s->param_presence_flags & PARAM_OUTSHIFT)
        if (get_bits1(gbp)) {
            for (ch = 0; ch <= s->max_matrix_channel; ch++) {
                s->output_shift[ch] = get_sbits(gbp, 4);
                if (s->output_shift[ch] < 0) {
                    avpriv_request_sample(m->avctx, "Negative output_shift");
                    s->output_shift[ch] = 0;
                }
            }
            if (substr == m->max_decoded_substream)
                m->dsp.mlp_pack_output = m->dsp.mlp_select_pack_output(s->ch_assign,
                                                                       s->output_shift,
                                                                       s->max_matrix_channel,
                                                                       m->avctx->sample_fmt == AV_SAMPLE_FMT_S32);
        }

    if (s->param_presence_flags & PARAM_QUANTSTEP)
        if (get_bits1(gbp))
            for (ch = 0; ch <= s->max_channel; ch++) {
                s->quant_step_size[ch] = get_bits(gbp, 4);

                recompute_sho |= 1<<ch;
            }

    for (ch = s->min_channel; ch <= s->max_channel; ch++)
        if (get_bits1(gbp)) {
            recompute_sho |= 1<<ch;
            if ((ret = read_channel_params(m, substr, gbp, ch)) < 0)
                goto fail;
        }


fail:
    for (ch = 0; ch <= s->max_channel; ch++) {
        if (recompute_sho & (1<<ch)) {
            ChannelParams *cp = &s->channel_params[ch];

            if (cp->codebook > 0 && cp->huff_lsbs < s->quant_step_size[ch]) {
                if (ret >= 0) {
                    av_log(m->avctx, AV_LOG_ERROR, "quant_step_size larger than huff_lsbs\n");
                    ret = AVERROR_INVALIDDATA;
                }
                s->quant_step_size[ch] = 0;
            }

            cp->sign_huff_offset = calculate_sign_huff(m, substr, ch);
        }
    }
    return ret;
}