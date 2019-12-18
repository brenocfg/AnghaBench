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
struct TYPE_3__ {int framenum; float*** time_samples; unsigned int* ch_pres; int /*<<< orphan*/ **** lpc_coeff; } ;
typedef  TYPE_1__ DCALbrDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  predict (float*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void synth_lpc(DCALbrDecoder *s, int ch1, int ch2, int sb)
{
    int f = s->framenum & 1;
    int ch;

    for (ch = ch1; ch <= ch2; ch++) {
        float *samples = s->time_samples[ch][sb];

        if (!(s->ch_pres[ch] & (1U << sb)))
            continue;

        if (sb < 2) {
            predict(samples,      s->lpc_coeff[f^1][ch][sb][1],  16);
            predict(samples + 16, s->lpc_coeff[f  ][ch][sb][0],  64);
            predict(samples + 80, s->lpc_coeff[f  ][ch][sb][1],  48);
        } else {
            predict(samples,      s->lpc_coeff[f^1][ch][sb][0],  16);
            predict(samples + 16, s->lpc_coeff[f  ][ch][sb][0], 112);
        }
    }
}