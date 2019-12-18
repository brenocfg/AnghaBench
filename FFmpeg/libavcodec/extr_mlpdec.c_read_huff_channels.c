#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  table; } ;
struct TYPE_8__ {int codebook; int huff_lsbs; scalar_t__ sign_huff_offset; } ;
struct TYPE_7__ {int** sample_buffer; int /*<<< orphan*/ ** bypassed_lsbs; TYPE_1__* substream; } ;
struct TYPE_6__ {unsigned int num_primitive_matrices; unsigned int blockpos; unsigned int min_channel; unsigned int max_channel; int* quant_step_size; TYPE_3__* channel_params; scalar_t__* lsb_bypass; } ;
typedef  TYPE_1__ SubStream ;
typedef  TYPE_2__ MLPDecodeContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ ChannelParams ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int VLC_BITS ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 TYPE_5__* huff_vlc ; 

__attribute__((used)) static inline int read_huff_channels(MLPDecodeContext *m, GetBitContext *gbp,
                                     unsigned int substr, unsigned int pos)
{
    SubStream *s = &m->substream[substr];
    unsigned int mat, channel;

    for (mat = 0; mat < s->num_primitive_matrices; mat++)
        if (s->lsb_bypass[mat])
            m->bypassed_lsbs[pos + s->blockpos][mat] = get_bits1(gbp);

    for (channel = s->min_channel; channel <= s->max_channel; channel++) {
        ChannelParams *cp = &s->channel_params[channel];
        int codebook = cp->codebook;
        int quant_step_size = s->quant_step_size[channel];
        int lsb_bits = cp->huff_lsbs - quant_step_size;
        int result = 0;

        if (codebook > 0)
            result = get_vlc2(gbp, huff_vlc[codebook-1].table,
                            VLC_BITS, (9 + VLC_BITS - 1) / VLC_BITS);

        if (result < 0)
            return AVERROR_INVALIDDATA;

        if (lsb_bits > 0)
            result = (result << lsb_bits) + get_bits(gbp, lsb_bits);

        result  += cp->sign_huff_offset;
        result *= 1 << quant_step_size;

        m->sample_buffer[pos + s->blockpos][channel] = result;
    }

    return 0;
}