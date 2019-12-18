#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {size_t frame_len_bits; size_t block_len_bits; float** exponents; int block_len; int version; int /*<<< orphan*/  pb; int /*<<< orphan*/ ** exponent_bands; } ;
typedef  TYPE_1__ WMACodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int* ff_aac_scalefactor_bits ; 
 int* ff_aac_scalefactor_code ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void encode_exp_vlc(WMACodecContext *s, int ch, const int *exp_param)
{
    int last_exp;
    const uint16_t *ptr;
    float *q, *q_end;

    ptr   = s->exponent_bands[s->frame_len_bits - s->block_len_bits];
    q     = s->exponents[ch];
    q_end = q + s->block_len;
    if (s->version == 1) {
        last_exp = *exp_param++;
        av_assert0(last_exp - 10 >= 0 && last_exp - 10 < 32);
        put_bits(&s->pb, 5, last_exp - 10);
        q += *ptr++;
    } else
        last_exp = 36;
    while (q < q_end) {
        int exp  = *exp_param++;
        int code = exp - last_exp + 60;
        av_assert1(code >= 0 && code < 120);
        put_bits(&s->pb, ff_aac_scalefactor_bits[code],
                 ff_aac_scalefactor_code[code]);
        /* XXX: use a table */
        q       += *ptr++;
        last_exp = exp;
    }
}