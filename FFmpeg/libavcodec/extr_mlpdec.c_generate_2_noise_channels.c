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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int int8_t ;
struct TYPE_5__ {int** sample_buffer; TYPE_1__* substream; } ;
struct TYPE_4__ {int noisegen_seed; unsigned int max_matrix_channel; unsigned int blockpos; int noise_shift; } ;
typedef  TYPE_1__ SubStream ;
typedef  TYPE_2__ MLPDecodeContext ;

/* Variables and functions */

__attribute__((used)) static void generate_2_noise_channels(MLPDecodeContext *m, unsigned int substr)
{
    SubStream *s = &m->substream[substr];
    unsigned int i;
    uint32_t seed = s->noisegen_seed;
    unsigned int maxchan = s->max_matrix_channel;

    for (i = 0; i < s->blockpos; i++) {
        uint16_t seed_shr7 = seed >> 7;
        m->sample_buffer[i][maxchan+1] = ((int8_t)(seed >> 15)) * (1 << s->noise_shift);
        m->sample_buffer[i][maxchan+2] = ((int8_t) seed_shr7)   * (1 << s->noise_shift);

        seed = (seed << 16) ^ seed_shr7 ^ (seed_shr7 << 5);
    }

    s->noisegen_seed = seed;
}