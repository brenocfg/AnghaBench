#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mant_groups ;
struct TYPE_5__ {int* start_freq; int* end_freq; int** fixed_coeffs; int*** pre_mantissa; int** dexps; int /*<<< orphan*/ * channel_uses_aht; } ;
typedef  TYPE_1__ AC3DecodeContext ;

/* Variables and functions */
 scalar_t__ CONFIG_EAC3_DECODER ; 
 int /*<<< orphan*/  ac3_decode_transform_coeffs_ch (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_eac3_decode_transform_coeffs_aht_ch (TYPE_1__*,int) ; 

__attribute__((used)) static inline void decode_transform_coeffs_ch(AC3DecodeContext *s, int blk,
                                              int ch, mant_groups *m)
{
    if (!s->channel_uses_aht[ch]) {
        ac3_decode_transform_coeffs_ch(s, ch, m);
    } else {
        /* if AHT is used, mantissas for all blocks are encoded in the first
           block of the frame. */
        int bin;
        if (CONFIG_EAC3_DECODER && !blk)
            ff_eac3_decode_transform_coeffs_aht_ch(s, ch);
        for (bin = s->start_freq[ch]; bin < s->end_freq[ch]; bin++) {
            s->fixed_coeffs[ch][bin] = s->pre_mantissa[ch][bin][blk] >> s->dexps[ch][bin];
        }
    }
}