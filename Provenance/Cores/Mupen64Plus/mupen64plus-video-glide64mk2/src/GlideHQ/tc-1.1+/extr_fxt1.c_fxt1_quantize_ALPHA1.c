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
 size_t ACOMP ; 
 size_t BCOMP ; 
 int /*<<< orphan*/  CALCCDOT (int,int const,int const,float*,float,int*) ; 
 size_t GCOMP ; 
 int /*<<< orphan*/  MAKEIVEC (int const,int const,float*,float,float*,float*) ; 
 int MAX_COMP ; 
 int N_TEXELS ; 
 int /*<<< orphan*/  Q_MOV32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Q_OR32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Q_SHL (int /*<<< orphan*/ ,int) ; 
 size_t RCOMP ; 

__attribute__((used)) static void
fxt1_quantize_ALPHA1 (dword *cc,
		      byte input[N_TEXELS][MAX_COMP])
{
    const int n_vect = 3; /* highest vector number in each microtile */
    const int n_comp = 4; /* 4 components: R, G, B, A */
    float vec[1 + 1 + 1][MAX_COMP]; /* 1.5 extrema for each sub-block */
    float b, iv[MAX_COMP]; /* interpolation vector */
    int i, j, k;
    qword hi; /* high quadword */
    dword lohi, lolo; /* low quadword: hi dword, lo dword */

    int minSum;
    int maxSum;
    int minColL = 0, maxColL = 0;
    int minColR = 0, maxColR = 0;
    int sumL = 0, sumR = 0;

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
	sumL += sum;
    }
#ifndef YUV
    minSum = 2000; /* big enough */
#else
    minSum = 2000000;
#endif
    maxSum = -1; /* small enough */
    for (; k < N_TEXELS; k++) {
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
	sumR += sum;
    }

    /* choose the common vector (yuck!) */
    {
	int j1, j2;
	int v1 = 0, v2 = 0;
	float err = 1e9; /* big enough */
	float tv[2 * 2][MAX_COMP]; /* 2 extrema for each sub-block */
	for (i = 0; i < n_comp; i++) {
	    tv[0][i] = input[minColL][i];
	    tv[1][i] = input[maxColL][i];
	    tv[2][i] = input[minColR][i];
	    tv[3][i] = input[maxColR][i];
	}
	for (j1 = 0; j1 < 2; j1++) {
	    for (j2 = 2; j2 < 4; j2++) {
		float e = 0.0F;
		for (i = 0; i < n_comp; i++) {
		    e += (tv[j1][i] - tv[j2][i]) * (tv[j1][i] - tv[j2][i]);
		}
		if (e < err) {
		    err = e;
		    v1 = j1;
		    v2 = j2;
		}
	    }
	}
	for (i = 0; i < n_comp; i++) {
	    vec[0][i] = tv[1 - v1][i];
	    vec[1][i] = (tv[v1][i] * sumL + tv[v2][i] * sumR) / (sumL + sumR);
	    vec[2][i] = tv[5 - v2][i];
	}
    }

    /* left microtile */
    cc[0] = 0;
    if (minColL != maxColL) {
	/* compute interpolation vector */
	MAKEIVEC(n_vect, n_comp, iv, b, vec[0], vec[1]);

	/* add in texels */
	lolo = 0;
	for (k = N_TEXELS / 2 - 1; k >= 0; k--) {
	    int texel;
	    /* interpolate color */
	    CALCCDOT(texel, n_vect, n_comp, iv, b, input[k]);
	    /* add in texel */
	    lolo <<= 2;
	    lolo |= texel;
	}

	cc[0] = lolo;
    }

    /* right microtile */
    cc[1] = 0;
    if (minColR != maxColR) {
	/* compute interpolation vector */
	MAKEIVEC(n_vect, n_comp, iv, b, vec[2], vec[1]);

	/* add in texels */
	lohi = 0;
	for (k = N_TEXELS - 1; k >= N_TEXELS / 2; k--) {
	    int texel;
	    /* interpolate color */
	    CALCCDOT(texel, n_vect, n_comp, iv, b, input[k]);
	    /* add in texel */
	    lohi <<= 2;
	    lohi |= texel;
	}

	cc[1] = lohi;
    }

    Q_MOV32(hi, 7); /* alpha = "011" + lerp = 1 */
    for (j = n_vect - 1; j >= 0; j--) {
	/* add in alphas */
	Q_SHL(hi, 5);
	Q_OR32(hi, (dword)(vec[j][ACOMP] / 8.0F));
    }
    for (j = n_vect - 1; j >= 0; j--) {
	for (i = 0; i < n_comp - 1; i++) {
	    /* add in colors */
	    Q_SHL(hi, 5);
	    Q_OR32(hi, (dword)(vec[j][i] / 8.0F));
	}
    }
    ((qword *)cc)[1] = hi;
}