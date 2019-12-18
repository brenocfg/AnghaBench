#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float* error_energy; } ;
struct TYPE_4__ {int start_band; int end_band; int* fine_bits; int channels; TYPE_2__* block; } ;
typedef  int /*<<< orphan*/  OpusRangeCoder ;
typedef  TYPE_1__ CeltFrame ;
typedef  TYPE_2__ CeltBlock ;

/* Variables and functions */
 int av_clip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_opus_rc_put_raw (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  floor (float) ; 

__attribute__((used)) static void celt_quant_fine(CeltFrame *f, OpusRangeCoder *rc)
{
    for (int i = f->start_band; i < f->end_band; i++) {
        if (!f->fine_bits[i])
            continue;
        for (int ch = 0; ch < f->channels; ch++) {
            CeltBlock *block = &f->block[ch];
            int quant, lim = (1 << f->fine_bits[i]);
            float offset, diff = 0.5f - block->error_energy[i];
            quant = av_clip(floor(diff*lim), 0, lim - 1);
            ff_opus_rc_put_raw(rc, quant, f->fine_bits[i]);
            offset = 0.5f - ((quant + 0.5f) * (1 << (14 - f->fine_bits[i])) / 16384.0f);
            block->error_energy[i] -= offset;
        }
    }
}