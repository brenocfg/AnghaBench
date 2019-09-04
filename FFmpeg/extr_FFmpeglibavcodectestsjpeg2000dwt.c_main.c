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
typedef  int /*<<< orphan*/  AVLFG ;

/* Variables and functions */
 int /*<<< orphan*/  FFMIN (int,int) ; 
 int /*<<< orphan*/  FF_DWT53 ; 
 int /*<<< orphan*/  FF_DWT97_INT ; 
 int FF_DWT_MAX_DECLVLS ; 
 int MAX_W ; 
 int* array ; 
 int* arrayf ; 
 int av_lfg_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_lfg_init (int /*<<< orphan*/ *,int) ; 
 int* ref ; 
 int* reff ; 
 int test_dwt (int*,int*,int**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int test_dwtf (int*,int*,int**,int,double) ; 

int main(void) {
    AVLFG prng;
    int i,j;
    int border[2][2];
    int ret, decomp_levels;

    av_lfg_init(&prng, 1);

    for (i = 0; i<MAX_W * MAX_W; i++)
        arrayf[i] = reff[i] = array[i] = ref[i] =  av_lfg_get(&prng) % 2048;

    for (i = 0; i < 100; i++) {
        for (j=0; j<4; j++)
            border[j>>1][j&1] = av_lfg_get(&prng) % MAX_W;
        if (border[0][0] >= border[0][1] || border[1][0] >= border[1][1])
            continue;
        decomp_levels = av_lfg_get(&prng) % FF_DWT_MAX_DECLVLS;

        ret = test_dwt(array, ref, border, decomp_levels, FF_DWT53, 0);
        if (ret)
            return ret;
        ret = test_dwt(array, ref, border, decomp_levels, FF_DWT97_INT, FFMIN(7+5*decomp_levels, 15+3*decomp_levels));
        if (ret)
            return ret;
        ret = test_dwtf(arrayf, reff, border, decomp_levels, 0.05);
        if (ret)
            return ret;
    }

    return 0;
}