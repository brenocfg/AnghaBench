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

/* Variables and functions */
 int BLOCKSIZE ; 
 int /*<<< orphan*/  LPC_ORDER ; 
 int /*<<< orphan*/  ff_celp_lp_synthesis_filterf (float*,float const*,float*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  orthogonalize (float*,float const*) ; 

__attribute__((used)) static void get_match_score(float *work, const float *coefs, float *vect,
                            const float *ortho1, const float *ortho2,
                            const float *data, float *score, float *gain)
{
    float c, g;
    int i;

    ff_celp_lp_synthesis_filterf(work, coefs, vect, BLOCKSIZE, LPC_ORDER);
    if (ortho1)
        orthogonalize(work, ortho1);
    if (ortho2)
        orthogonalize(work, ortho2);
    c = g = 0;
    for (i = 0; i < BLOCKSIZE; i++) {
        g += work[i] * work[i];
        c += data[i] * work[i];
    }
    if (c <= 0) {
        *score = 0;
        return;
    }
    *gain = c / g;
    *score = *gain * c;
}