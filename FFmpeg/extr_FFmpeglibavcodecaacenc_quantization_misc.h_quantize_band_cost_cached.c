#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct AACEncContext {scalar_t__ quantize_band_cost_cache_generation; TYPE_1__** quantize_band_cost_cache; } ;
struct TYPE_2__ {scalar_t__ generation; int cb; int rtz; float rd; int bits; float energy; } ;
typedef  TYPE_1__ AACQuantizeBandCostCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert1 (int) ; 
 float quantize_band_cost (struct AACEncContext*,float const*,float const*,int,int,int,float const,float const,int*,float*,int) ; 

__attribute__((used)) static inline float quantize_band_cost_cached(struct AACEncContext *s, int w, int g, const float *in,
                                const float *scaled, int size, int scale_idx,
                                int cb, const float lambda, const float uplim,
                                int *bits, float *energy, int rtz)
{
    AACQuantizeBandCostCacheEntry *entry;
    av_assert1(scale_idx >= 0 && scale_idx < 256);
    entry = &s->quantize_band_cost_cache[scale_idx][w*16+g];
    if (entry->generation != s->quantize_band_cost_cache_generation || entry->cb != cb || entry->rtz != rtz) {
        entry->rd = quantize_band_cost(s, in, scaled, size, scale_idx,
                                       cb, lambda, uplim, &entry->bits, &entry->energy, rtz);
        entry->cb = cb;
        entry->rtz = rtz;
        entry->generation = s->quantize_band_cost_cache_generation;
    }
    if (bits)
        *bits = entry->bits;
    if (energy)
        *energy = entry->energy;
    return entry->rd;
}