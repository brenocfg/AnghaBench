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
typedef  int int32_t ;
struct TYPE_7__ {int huff_lsbs; int codebook; int huff_offset; } ;
struct TYPE_6__ {TYPE_1__* substream; } ;
struct TYPE_5__ {int* quant_step_size; TYPE_3__* channel_params; } ;
typedef  TYPE_1__ SubStream ;
typedef  TYPE_2__ MLPDecodeContext ;
typedef  TYPE_3__ ChannelParams ;

/* Variables and functions */

__attribute__((used)) static inline int32_t calculate_sign_huff(MLPDecodeContext *m,
                                          unsigned int substr, unsigned int ch)
{
    SubStream *s = &m->substream[substr];
    ChannelParams *cp = &s->channel_params[ch];
    int lsb_bits = cp->huff_lsbs - s->quant_step_size[ch];
    int sign_shift = lsb_bits + (cp->codebook ? 2 - cp->codebook : -1);
    int32_t sign_huff_offset = cp->huff_offset;

    if (cp->codebook > 0)
        sign_huff_offset -= 7 << lsb_bits;

    if (sign_shift >= 0)
        sign_huff_offset -= 1 << sign_shift;

    return sign_huff_offset;
}