#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  int int16_t ;
typedef  enum AlacRawDataBlockType { ____Placeholder_AlacRawDataBlockType } AlacRawDataBlockType ;
struct TYPE_13__ {int rice_modifier; } ;
struct TYPE_15__ {int frame_size; int extra_bits; int** predictor_buf; int** sample_buf; int interlacing_shift; int interlacing_leftweight; TYPE_3__* lpc; TYPE_2__ rc; TYPE_1__* avctx; scalar_t__ write_sample_size; scalar_t__ verbatim; int /*<<< orphan*/  pbctx; } ;
struct TYPE_14__ {int lpc_quant; int lpc_order; int const* lpc_coeff; } ;
struct TYPE_12__ {scalar_t__ sample_fmt; int bits_per_raw_sample; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_4__ AlacEncodeContext ;

/* Variables and functions */
 scalar_t__ AV_SAMPLE_FMT_S32P ; 
 int TYPE_CPE ; 
 int /*<<< orphan*/  alac_entropy_coder (TYPE_4__*,int) ; 
 int /*<<< orphan*/  alac_linear_predictor (TYPE_4__*,int) ; 
 int /*<<< orphan*/  alac_stereo_decorrelation (TYPE_4__*) ; 
 int /*<<< orphan*/  calc_predictor_params (TYPE_4__*,int) ; 
 int /*<<< orphan*/  init_sample_buffers (TYPE_4__*,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_sbits (int /*<<< orphan*/ *,int,int const) ; 
 int /*<<< orphan*/  write_element_header (TYPE_4__*,int,int) ; 

__attribute__((used)) static void write_element(AlacEncodeContext *s,
                          enum AlacRawDataBlockType element, int instance,
                          const uint8_t *samples0, const uint8_t *samples1)
{
    const uint8_t *samples[2] = { samples0, samples1 };
    int i, j, channels;
    int prediction_type = 0;
    PutBitContext *pb = &s->pbctx;

    channels = element == TYPE_CPE ? 2 : 1;

    if (s->verbatim) {
        write_element_header(s, element, instance);
        /* samples are channel-interleaved in verbatim mode */
        if (s->avctx->sample_fmt == AV_SAMPLE_FMT_S32P) {
            int shift = 32 - s->avctx->bits_per_raw_sample;
            const int32_t *samples_s32[2] = { (const int32_t *)samples0,
                                              (const int32_t *)samples1 };
            for (i = 0; i < s->frame_size; i++)
                for (j = 0; j < channels; j++)
                    put_sbits(pb, s->avctx->bits_per_raw_sample,
                              samples_s32[j][i] >> shift);
        } else {
            const int16_t *samples_s16[2] = { (const int16_t *)samples0,
                                              (const int16_t *)samples1 };
            for (i = 0; i < s->frame_size; i++)
                for (j = 0; j < channels; j++)
                    put_sbits(pb, s->avctx->bits_per_raw_sample,
                              samples_s16[j][i]);
        }
    } else {
        s->write_sample_size = s->avctx->bits_per_raw_sample - s->extra_bits +
                               channels - 1;

        init_sample_buffers(s, channels, samples);
        write_element_header(s, element, instance);

        // extract extra bits if needed
        if (s->extra_bits) {
            uint32_t mask = (1 << s->extra_bits) - 1;
            for (j = 0; j < channels; j++) {
                int32_t *extra = s->predictor_buf[j];
                int32_t *smp   = s->sample_buf[j];
                for (i = 0; i < s->frame_size; i++) {
                    extra[i] = smp[i] & mask;
                    smp[i] >>= s->extra_bits;
                }
            }
        }

        if (channels == 2)
            alac_stereo_decorrelation(s);
        else
            s->interlacing_shift = s->interlacing_leftweight = 0;
        put_bits(pb, 8, s->interlacing_shift);
        put_bits(pb, 8, s->interlacing_leftweight);

        for (i = 0; i < channels; i++) {
            calc_predictor_params(s, i);

            put_bits(pb, 4, prediction_type);
            put_bits(pb, 4, s->lpc[i].lpc_quant);

            put_bits(pb, 3, s->rc.rice_modifier);
            put_bits(pb, 5, s->lpc[i].lpc_order);
            // predictor coeff. table
            for (j = 0; j < s->lpc[i].lpc_order; j++)
                put_sbits(pb, 16, s->lpc[i].lpc_coeff[j]);
        }

        // write extra bits if needed
        if (s->extra_bits) {
            for (i = 0; i < s->frame_size; i++) {
                for (j = 0; j < channels; j++) {
                    put_bits(pb, s->extra_bits, s->predictor_buf[j][i]);
                }
            }
        }

        // apply lpc and entropy coding to audio samples
        for (i = 0; i < channels; i++) {
            alac_linear_predictor(s, i);

            // TODO: determine when this will actually help. for now it's not used.
            if (prediction_type == 15) {
                // 2nd pass 1st order filter
                int32_t *residual = s->predictor_buf[i];
                for (j = s->frame_size - 1; j > 0; j--)
                    residual[j] -= residual[j - 1];
            }
            alac_entropy_coder(s, i);
        }
    }
}