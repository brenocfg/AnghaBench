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
struct TYPE_5__ {float* energy; } ;
struct TYPE_4__ {int start_band; int end_band; int* fine_bits; int channels; TYPE_2__* block; } ;
typedef  int /*<<< orphan*/  OpusRangeCoder ;
typedef  TYPE_1__ CeltFrame ;
typedef  TYPE_2__ CeltBlock ;

/* Variables and functions */
 int ff_opus_rc_get_raw (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void celt_decode_fine_energy(CeltFrame *f, OpusRangeCoder *rc)
{
    int i;
    for (i = f->start_band; i < f->end_band; i++) {
        int j;
        if (!f->fine_bits[i])
            continue;

        for (j = 0; j < f->channels; j++) {
            CeltBlock *block = &f->block[j];
            int q2;
            float offset;
            q2 = ff_opus_rc_get_raw(rc, f->fine_bits[i]);
            offset = (q2 + 0.5f) * (1 << (14 - f->fine_bits[i])) / 16384.0f - 0.5f;
            block->energy[i] += offset;
        }
    }
}