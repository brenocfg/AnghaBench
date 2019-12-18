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
struct TYPE_3__ {float const* dct_table; } ;
typedef  TYPE_1__ AudioRNNContext ;

/* Variables and functions */
 int NB_BANDS ; 
 float sqrtf (float) ; 

__attribute__((used)) static void dct(AudioRNNContext *s, float *out, const float *in)
{
    for (int i = 0; i < NB_BANDS; i++) {
        float sum = 0.f;

        for (int j = 0; j < NB_BANDS; j++) {
            sum += in[j] * s->dct_table[j * NB_BANDS + i];
        }
        out[i] = sum * sqrtf(2.f / 22);
    }
}