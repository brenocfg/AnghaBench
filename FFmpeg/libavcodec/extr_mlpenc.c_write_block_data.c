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
typedef  int int32_t ;
struct TYPE_9__ {int huff_lsbs; int codebook; int huff_offset; } ;
struct TYPE_8__ {int* quant_step_size; unsigned int blocksize; } ;
struct TYPE_7__ {int* write_buffer; TYPE_4__* cur_channel_params; TYPE_1__* cur_restart_header; TYPE_3__* cur_decoding_params; } ;
struct TYPE_6__ {unsigned int min_channel; unsigned int max_channel; } ;
typedef  TYPE_1__ RestartHeader ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_2__ MLPEncodeContext ;
typedef  TYPE_3__ DecodingParams ;
typedef  TYPE_4__ ChannelParams ;

/* Variables and functions */
 int MAX_CHANNELS ; 
 int /*<<< orphan*/ *** ff_mlp_huffman_tables ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_sbits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void write_block_data(MLPEncodeContext *ctx, PutBitContext *pb)
{
    DecodingParams *dp = ctx->cur_decoding_params;
    RestartHeader  *rh = ctx->cur_restart_header;
    int32_t *sample_buffer = ctx->write_buffer;
    int32_t sign_huff_offset[MAX_CHANNELS];
    int codebook_index      [MAX_CHANNELS];
    int lsb_bits            [MAX_CHANNELS];
    unsigned int i, ch;

    for (ch = rh->min_channel; ch <= rh->max_channel; ch++) {
        ChannelParams *cp = &ctx->cur_channel_params[ch];
        int sign_shift;

        lsb_bits        [ch] = cp->huff_lsbs - dp->quant_step_size[ch];
        codebook_index  [ch] = cp->codebook  - 1;
        sign_huff_offset[ch] = cp->huff_offset;

        sign_shift = lsb_bits[ch] - 1;

        if (cp->codebook > 0) {
            sign_huff_offset[ch] -= 7 << lsb_bits[ch];
            sign_shift += 3 - cp->codebook;
        }

        /* Unsign if needed. */
        if (sign_shift >= 0)
            sign_huff_offset[ch] -= 1 << sign_shift;
    }

    for (i = 0; i < dp->blocksize; i++) {
        for (ch = rh->min_channel; ch <= rh->max_channel; ch++) {
            int32_t sample = *sample_buffer++ >> dp->quant_step_size[ch];

            sample -= sign_huff_offset[ch];

            if (codebook_index[ch] >= 0) {
                int vlc = sample >> lsb_bits[ch];
                put_bits(pb, ff_mlp_huffman_tables[codebook_index[ch]][vlc][1],
                             ff_mlp_huffman_tables[codebook_index[ch]][vlc][0]);
            }

            put_sbits(pb, lsb_bits[ch], sample);
        }
        sample_buffer += 2; /* noise channels */
    }

    ctx->write_buffer = sample_buffer;
}