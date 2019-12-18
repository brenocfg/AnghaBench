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
typedef  int /*<<< orphan*/  qword ;
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
 int /*<<< orphan*/  Q_MOV32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Q_OR32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Q_SHL (int /*<<< orphan*/ ,int) ; 
 size_t RCOMP ; 

__attribute__((used)) static void
fxt1_quantize_MIXED1 (dword *cc,
		      byte input[N_TEXELS][MAX_COMP])
{
    const int n_vect = 2; /* highest vector number in each microtile */
    const int n_comp = 3; /* 3 components: R, G, B */
    byte vec[2 * 2][MAX_COMP]; /* 2 extrema for each sub-block */
    float b, iv[MAX_COMP]; /* interpolation vector */
    int i, j, k;
    qword hi; /* high quadword */
    dword lohi, lolo; /* low quadword: hi dword, lo dword */

    int minSum;
    int maxSum;
    int minColL = 0, maxColL = -1;
    int minColR = 0, maxColR = -1;

    /* Our solution here is to find the darkest and brightest colors in
     * the 4x4 tile and use those as the two representative colors.
     * There are probably better algorithms to use (histogram-based).
     */
#ifndef YUV
    minSum = 2000; /* big enough */
#else
    minSum = 2000000;
#endif
    maxSum = -1; /* small enough */
    for (k = 0; k < N_TEXELS / 2; k++) {
	if (!ISTBLACK(input[k])) {
	    int sum = 0;
#ifndef YUV
	    for (i = 0; i < n_comp; i++) {
		sum += input[k][i];
	    }
#else
            sum = 299 * input[k][RCOMP] + 587 * input[k][GCOMP] +  114 * input[k][BCOMP];
#endif
	    if (minSum > sum) {
		minSum = sum;
		minColL = k;
	    }
	    if (maxSum < sum) {
		maxSum = sum;
		maxColL = k;
	    }
	}
    }
#ifndef YUV
    minSum = 2000; /* big enough */
#else
    minSum = 2000000;
#endif
    maxSum = -1; /* small enough */
    for (; k < N_TEXELS; k++) {
	if (!ISTBLACK(input[k])) {
	    int sum = 0;
#ifndef YUV
	    for (i = 0; i < n_comp; i++) {
		sum += input[k][i];
	    }
#else
            sum = 299 * input[k][RCOMP] + 587 * input[k][GCOMP] +  114 * input[k][BCOMP];
#endif
	    if (minSum > sum) {
		minSum = sum;
		minColR = k;
	    }
	    if (maxSum < sum) {
		maxSum = sum;
		maxColR = k;
	    }
	}
    }

    /* left microtile */
    if (maxColL == -1) {
	/* all transparent black */
	cc[0] = 0xFFFFFFFF;
	for (i = 0; i < n_comp; i++) {
	    vec[0][i] = 0;
	    vec[1][i] = 0;
	}
    } else {
	cc[0] = 0;
	for (i = 0; i < n_comp; i++) {
	    vec[0][i] = input[minColL][i];
	    vec[1][i] = input[maxColL][i];
	}
	if (minColL != maxColL) {
	    /* compute interpolation vector */
	    MAKEIVEC(n_vect, n_comp, iv, b, vec[0], vec[1]);

	    /* add in texels */
	    lolo = 0;
	    for (k = N_TEXELS / 2 - 1; k >= 0; k--) {
		int texel = n_vect + 1;	/* transparent black */
		if (!ISTBLACK(input[k])) {
		    /* interpolate color */
		    CALCCDOT(texel, n_vect, n_comp, iv, b, input[k]);
		}
		/* add in texel */
		lolo <<= 2;
		lolo |= texel;
	    }
	    cc[0] = lolo;
	}
    }

    /* right microtile */
    if (maxColR == -1) {
	/* all transparent black */
	cc[1] = 0xFFFFFFFF;
	for (i = 0; i < n_comp; i++) {
	    vec[2][i] = 0;
	    vec[3][i] = 0;
	}
    } else {
	cc[1] = 0;
	for (i = 0; i < n_comp; i++) {
	    vec[2][i] = input[minColR][i];
	    vec[3][i] = input[maxColR][i];
	}
	if (minColR != maxColR) {
	    /* compute interpolation vector */
	    MAKEIVEC(n_vect, n_comp, iv, b, vec[2], vec[3]);

	    /* add in texels */
	    lohi = 0;
	    for (k = N_TEXELS - 1; k >= N_TEXELS / 2; k--) {
		int texel = n_vect + 1;	/* transparent black */
		if (!ISTBLACK(input[k])) {
		    /* interpolate color */
		    CALCCDOT(texel, n_vect, n_comp, iv, b, input[k]);
		}
		/* add in texel */
		lohi <<= 2;
		lohi |= texel;
	    }
	    cc[1] = lohi;
	}
    }

    Q_MOV32(hi, 9 | (vec[3][GCOMP] & 4) | ((vec[1][GCOMP] >> 1) & 2)); /* chroma = "1" */
    for (j = 2 * 2 - 1; j >= 0; j--) {
	for (i = 0; i < n_comp; i++) {
	    /* add in colors */
	    Q_SHL(hi, 5);
	    Q_OR32(hi, vec[j][i] >> 3);
	}
    }
    ((qword *)cc)[1] = hi;
}