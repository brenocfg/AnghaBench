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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  occ ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 double log2 (int) ; 
 int /*<<< orphan*/  memcpy (double*,double*,int) ; 

__attribute__((used)) static void find_best_state(uint8_t best_state[256][256],
                            const uint8_t one_state[256])
{
    int i, j, k, m;
    double l2tab[256];

    for (i = 1; i < 256; i++)
        l2tab[i] = log2(i / 256.0);

    for (i = 0; i < 256; i++) {
        double best_len[256];
        double p = i / 256.0;

        for (j = 0; j < 256; j++)
            best_len[j] = 1 << 30;

        for (j = FFMAX(i - 10, 1); j < FFMIN(i + 11, 256); j++) {
            double occ[256] = { 0 };
            double len      = 0;
            occ[j] = 1.0;

            if (!one_state[j])
                continue;

            for (k = 0; k < 256; k++) {
                double newocc[256] = { 0 };
                for (m = 1; m < 256; m++)
                    if (occ[m]) {
                        len -=occ[m]*(     p *l2tab[    m]
                                      + (1-p)*l2tab[256-m]);
                    }
                if (len < best_len[k]) {
                    best_len[k]      = len;
                    best_state[i][k] = j;
                }
                for (m = 1; m < 256; m++)
                    if (occ[m]) {
                        newocc[      one_state[      m]] += occ[m] * p;
                        newocc[256 - one_state[256 - m]] += occ[m] * (1 - p);
                    }
                memcpy(occ, newocc, sizeof(occ));
            }
        }
    }
}