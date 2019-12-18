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
typedef  int int8_t ;
typedef  unsigned int int16_t ;

/* Variables and functions */
 int BLOCKSIZE ; 
 unsigned int* ff_gain_exp_tab ; 
 unsigned int** ff_gain_val_tab ; 

__attribute__((used)) static void add_wav(int16_t *dest, int n, int skip_first, int *m,
                    const int16_t *s1, const int8_t *s2, const int8_t *s3)
{
    int i;
    int v[3];

    v[0] = 0;
    for (i=!skip_first; i<3; i++)
        v[i] = (ff_gain_val_tab[n][i] * (unsigned)m[i]) >> ff_gain_exp_tab[n];

    if (v[0]) {
        for (i=0; i < BLOCKSIZE; i++)
            dest[i] = (int)((s1[i]*(unsigned)v[0]) + s2[i]*v[1] + s3[i]*v[2]) >> 12;
    } else {
        for (i=0; i < BLOCKSIZE; i++)
            dest[i] = (             s2[i]*v[1] + s3[i]*v[2]) >> 12;
    }
}