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
typedef  int dword ;
typedef  int byte ;

/* Variables and functions */
 size_t BCOMP ; 
 int /*<<< orphan*/  CALCCDOT (int,int const,int const,float*,float,int*) ; 
 size_t GCOMP ; 
 int /*<<< orphan*/  ISTBLACK (int*) ; 
 int /*<<< orphan*/  MAKEIVEC (int const,int const,float*,float,int*,int*) ; 
 int MAX_COMP ; 
 int N_TEXELS ; 
 size_t RCOMP ; 

__attribute__((used)) static void
fxt1_quantize_HI (dword *cc,
		  byte input[N_TEXELS][MAX_COMP],
		  byte reord[N_TEXELS][MAX_COMP], int n)
{
    const int n_vect = 6; /* highest vector number */
    const int n_comp = 3; /* 3 components: R, G, B */
    float b = 0.0F;       /* phoudoin: silent compiler! */
    float iv[MAX_COMP];   /* interpolation vector */
    int i, k;
    dword hihi; /* high quadword: hi dword */

#ifndef YUV
    int minSum = 2000; /* big enough */
#else
    int minSum = 2000000;
#endif
    int maxSum = -1; /* small enough */
    int minCol = 0; /* phoudoin: silent compiler! */
    int maxCol = 0; /* phoudoin: silent compiler! */

    /* Our solution here is to find the darkest and brightest colors in
     * the 8x4 tile and use those as the two representative colors.
     * There are probably better algorithms to use (histogram-based).
     */
    for (k = 0; k < n; k++) {
	int sum = 0;
#ifndef YUV
	for (i = 0; i < n_comp; i++) {
	    sum += reord[k][i];
	}
#else
        sum = 299 * input[k][RCOMP] + 587 * input[k][GCOMP] +  114 * input[k][BCOMP];
#endif
	if (minSum > sum) {
	    minSum = sum;
	    minCol = k;
	}
	if (maxSum < sum) {
	    maxSum = sum;
	    maxCol = k;
	}
    }

    hihi = 0; /* cc-hi = "00" */
    for (i = 0; i < n_comp; i++) {
	/* add in colors */
	hihi <<= 5;
	hihi |= reord[maxCol][i] >> 3;
    }
    for (i = 0; i < n_comp; i++) {
	/* add in colors */
	hihi <<= 5;
	hihi |= reord[minCol][i] >> 3;
    }
    cc[3] = hihi;
    cc[0] = cc[1] = cc[2] = 0;

    /* compute interpolation vector */
    if (minCol != maxCol) {
	MAKEIVEC(n_vect, n_comp, iv, b, reord[minCol], reord[maxCol]);
    }

    /* add in texels */
    for (k = N_TEXELS - 1; k >= 0; k--) {
	int t = k * 3;
	dword *kk = (dword *)((byte *)cc + t / 8);
	int texel = n_vect + 1; /* transparent black */

	if (!ISTBLACK(input[k])) {
	    if (minCol != maxCol) {
		/* interpolate color */
		CALCCDOT(texel, n_vect, n_comp, iv, b, input[k]);
		/* add in texel */
		kk[0] |= texel << (t & 7);
	    }
	} else {
	    /* add in texel */
	    kk[0] |= texel << (t & 7);
	}
    }
}