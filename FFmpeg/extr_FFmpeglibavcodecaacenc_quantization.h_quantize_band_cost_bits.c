#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct AACEncContext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  quantize_and_encode_band_cost (struct AACEncContext*,int /*<<< orphan*/ *,float const*,int /*<<< orphan*/ *,float const*,int,int,int,float,float const,int*,float*,int) ; 

__attribute__((used)) static inline int quantize_band_cost_bits(struct AACEncContext *s, const float *in,
                                const float *scaled, int size, int scale_idx,
                                int cb, const float lambda, const float uplim,
                                int *bits, float *energy, int rtz)
{
    int auxbits;
    quantize_and_encode_band_cost(s, NULL, in, NULL, scaled, size, scale_idx,
                                         cb, 0.0f, uplim, &auxbits, energy, rtz);
    if (bits) {
        *bits = auxbits;
    }
    return auxbits;
}