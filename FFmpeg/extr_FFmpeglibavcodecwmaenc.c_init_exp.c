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
struct TYPE_3__ {size_t frame_len_bits; size_t block_len_bits; float** exponents; int block_len; float* max_exponent; int /*<<< orphan*/ ** exponent_bands; } ;
typedef  TYPE_1__ WMACodecContext ;

/* Variables and functions */
 float FFMAX (float,float) ; 
 float ff_exp10 (double) ; 

__attribute__((used)) static void init_exp(WMACodecContext *s, int ch, const int *exp_param)
{
    int n;
    const uint16_t *ptr;
    float v, *q, max_scale, *q_end;

    ptr       = s->exponent_bands[s->frame_len_bits - s->block_len_bits];
    q         = s->exponents[ch];
    q_end     = q + s->block_len;
    max_scale = 0;
    while (q < q_end) {
        /* XXX: use a table */
        v         = ff_exp10(*exp_param++ *(1.0 / 16.0));
        max_scale = FFMAX(max_scale, v);
        n         = *ptr++;
        do {
            *q++ = v;
        } while (--n);
    }
    s->max_exponent[ch] = max_scale;
}