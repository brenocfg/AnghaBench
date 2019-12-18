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
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
typedef  int int32_t ;
struct TYPE_7__ {unsigned int count; int* shift; unsigned int* outch; int** forco; } ;
struct TYPE_9__ {TYPE_2__ matrix_params; } ;
struct TYPE_8__ {int* sample_buffer; unsigned int num_channels; unsigned int number_of_samples; TYPE_1__* avctx; TYPE_4__* cur_decoding_params; } ;
struct TYPE_6__ {scalar_t__ sample_fmt; } ;
typedef  TYPE_2__ MatrixParams ;
typedef  TYPE_3__ MLPEncodeContext ;
typedef  TYPE_4__ DecodingParams ;

/* Variables and functions */
 scalar_t__ AV_SAMPLE_FMT_S16 ; 
 int MSB_MASK (unsigned int) ; 

__attribute__((used)) static void rematrix_channels(MLPEncodeContext *ctx)
{
    DecodingParams *dp = ctx->cur_decoding_params;
    MatrixParams *mp = &dp->matrix_params;
    int32_t *sample_buffer = ctx->sample_buffer;
    unsigned int mat, i, maxchan;

    maxchan = ctx->num_channels;

    for (mat = 0; mat < mp->count; mat++) {
        unsigned int msb_mask_bits = (ctx->avctx->sample_fmt == AV_SAMPLE_FMT_S16 ? 8 : 0) - mp->shift[mat];
        int32_t mask = MSB_MASK(msb_mask_bits);
        unsigned int outch = mp->outch[mat];

        sample_buffer = ctx->sample_buffer;
        for (i = 0; i < ctx->number_of_samples; i++) {
            unsigned int src_ch;
            int64_t accum = 0;

            for (src_ch = 0; src_ch < maxchan; src_ch++) {
                int32_t sample = *(sample_buffer + src_ch);
                accum += (int64_t) sample * mp->forco[mat][src_ch];
            }
            sample_buffer[outch] = (accum >> 14) & mask;

            sample_buffer += ctx->num_channels;
        }
    }
}