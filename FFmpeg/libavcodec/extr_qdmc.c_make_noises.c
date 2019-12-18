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
struct TYPE_3__ {size_t band_index; float* noise_buffer; } ;
typedef  TYPE_1__ QDMCContext ;

/* Variables and functions */
 int* noise_bands_size ; 
 int* qdmc_nodes ; 

__attribute__((used)) static void make_noises(QDMCContext *s)
{
    int i, j, n0, n1, n2, diff;
    float *nptr;

    for (j = 0; j < noise_bands_size[s->band_index]; j++) {
        n0 = qdmc_nodes[j + 21 * s->band_index    ];
        n1 = qdmc_nodes[j + 21 * s->band_index + 1];
        n2 = qdmc_nodes[j + 21 * s->band_index + 2];
        nptr = s->noise_buffer + 256 * j;

        for (i = 0; i + n0 < n1; i++, nptr++)
            nptr[0] = i / (float)(n1 - n0);

        diff = n2 - n1;
        nptr = s->noise_buffer + (j << 8) + n1 - n0;

        for (i = n1; i < n2; i++, nptr++, diff--)
            nptr[0] = diff / (float)(n2 - n1);
    }
}