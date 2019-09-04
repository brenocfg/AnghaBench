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
struct AACEncContext {int quantize_band_cost_cache_generation; int /*<<< orphan*/  quantize_band_cost_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ff_quantize_band_cost_cache_init(struct AACEncContext *s)
{
    ++s->quantize_band_cost_cache_generation;
    if (s->quantize_band_cost_cache_generation == 0) {
        memset(s->quantize_band_cost_cache, 0, sizeof(s->quantize_band_cost_cache));
        s->quantize_band_cost_cache_generation = 1;
    }
}