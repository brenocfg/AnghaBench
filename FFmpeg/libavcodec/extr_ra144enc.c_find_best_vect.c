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
typedef  float int8_t ;

/* Variables and functions */
 int BLOCKSIZE ; 
 int FIXED_CB_SIZE ; 
 int /*<<< orphan*/  get_match_score (float*,float const*,float*,float const*,float const*,float*,float*,float*) ; 

__attribute__((used)) static void find_best_vect(float *work, const float *coefs,
                           const int8_t cb[][BLOCKSIZE], const float *ortho1,
                           const float *ortho2, float *data, int *idx,
                           float *gain)
{
    int i, j;
    float g, score, best_score;
    float vect[BLOCKSIZE];

    *idx = *gain = best_score = 0;
    for (i = 0; i < FIXED_CB_SIZE; i++) {
        for (j = 0; j < BLOCKSIZE; j++)
            vect[j] = cb[i][j];
        get_match_score(work, coefs, vect, ortho1, ortho2, data, &score, &g);
        if (score > best_score) {
            best_score = score;
            *idx = i;
            *gain = g;
        }
    }
}