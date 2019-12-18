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
typedef  int /*<<< orphan*/  cba_vect ;
typedef  int /*<<< orphan*/  cb1_vect ;

/* Variables and functions */
 int BLOCKSIZE ; 
 int /*<<< orphan*/  LPC_ORDER ; 
 float** ff_cb1_vects ; 
 float** ff_cb2_vects ; 
 int /*<<< orphan*/  ff_celp_lp_synthesis_filterf (float*,float const*,float*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_best_vect (float*,float const*,float**,float*,float*,float*,int*,float*) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int /*<<< orphan*/  orthogonalize (float*,float*) ; 

__attribute__((used)) static void fixed_cb_search(float *work, const float *coefs, float *data,
                            int cba_idx, int *cb1_idx, int *cb2_idx)
{
    int i, ortho_cb1;
    float gain;
    float cba_vect[BLOCKSIZE], cb1_vect[BLOCKSIZE];
    float vect[BLOCKSIZE];

    /**
     * The filtered vector from the adaptive codebook can be retrieved from
     * work, because this function is called just after adaptive_cb_search().
     */
    if (cba_idx)
        memcpy(cba_vect, work, sizeof(cba_vect));

    find_best_vect(work, coefs, ff_cb1_vects, cba_idx ? cba_vect : NULL, NULL,
                   data, cb1_idx, &gain);

    /**
     * Re-calculate the filtered vector from the vector with maximum match score
     * and remove its contribution from input data.
     */
    if (gain) {
        for (i = 0; i < BLOCKSIZE; i++)
            vect[i] = ff_cb1_vects[*cb1_idx][i];
        ff_celp_lp_synthesis_filterf(work, coefs, vect, BLOCKSIZE, LPC_ORDER);
        if (cba_idx)
            orthogonalize(work, cba_vect);
        for (i = 0; i < BLOCKSIZE; i++)
            data[i] -= gain * work[i];
        memcpy(cb1_vect, work, sizeof(cb1_vect));
        ortho_cb1 = 1;
    } else
        ortho_cb1 = 0;

    find_best_vect(work, coefs, ff_cb2_vects, cba_idx ? cba_vect : NULL,
                   ortho_cb1 ? cb1_vect : NULL, data, cb2_idx, &gain);
}