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
typedef  int /*<<< orphan*/  input ;
typedef  int dword ;
typedef  int byte ;

/* Variables and functions */
 size_t ACOMP ; 
 size_t BCOMP ; 
 int /*<<< orphan*/  CALCCDOT (int,int const,int const,float*,float,int*) ; 
 int COLOR565 (int*) ; 
 size_t GCOMP ; 
 int /*<<< orphan*/  MAKEIVEC (int const,int const,float*,float,int*,int*) ; 
 int MAX_COMP ; 
 int N_TEXELS ; 
 int /*<<< orphan*/  Q_MOV32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_OR32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Q_SHL (int /*<<< orphan*/ ,int) ; 
 size_t RCOMP ; 
 int** dxtn_alpha_tlat ; 
 int** dxtn_color_tlat ; 
 int /*<<< orphan*/  memset (int**,int,int) ; 

__attribute__((used)) static void
dxt5_rgba_quantize (dword *cc, const byte *lines[], int comps)
{
    float b, iv[MAX_COMP];	/* interpolation vector */

    qword lo;			/* low quadword */
    dword hihi;		/* high quadword: high dword */
    int color0, color1;
    const int n_vect = 3;
    const int n_comp = 3;

#ifndef YUV
    int minSum = 2000;          /* big enough */
#else
    int minSum = 2000000;
#endif
    int maxSum = -1;		/* small enough */
    int minCol = 0;		/* phoudoin: silent compiler! */
    int maxCol = 0;		/* phoudoin: silent compiler! */
    int alpha0 = 2000;		/* big enough */
    int alpha1 = -1;		/* small enough */
    int anyZero = 0, anyOne = 0;
    int a_vect;

    byte input[N_TEXELS][MAX_COMP];
    int i, k, l;

    if (comps == 3) {
	/* make the whole block opaque */
	memset(input, -1, sizeof(input));
    }

    /* 4 texels each line */
#ifndef ARGB
    for (l = 0; l < 4; l++) {
	for (k = 0; k < 4; k++) {
	    for (i = 0; i < comps; i++) {
		input[k + l * 4][i] = *lines[l]++;
	    }
	}
    }
#else
    /* H.Morii - support for ARGB inputs */
    for (l = 0; l < 4; l++) {
	for (k = 0; k < 4; k++) {
          input[k + l * 4][2] = *lines[l]++;
          input[k + l * 4][1] = *lines[l]++;
          input[k + l * 4][0] = *lines[l]++;
          if (comps == 4) input[k + l * 4][3] = *lines[l]++;
	}
    }
#endif

    /* Our solution here is to find the darkest and brightest colors in
     * the 4x4 tile and use those as the two representative colors.
     * There are probably better algorithms to use (histogram-based).
     */
    for (k = 0; k < N_TEXELS; k++) {
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
	    minCol = k;
	}
	if (maxSum < sum) {
	    maxSum = sum;
	    maxCol = k;
	}
	if (alpha0 > input[k][ACOMP]) {
	    alpha0 = input[k][ACOMP];
	}
	if (alpha1 < input[k][ACOMP]) {
	    alpha1 = input[k][ACOMP];
	}
	if (input[k][ACOMP] == 0) {
	    anyZero = 1;
	}
	if (input[k][ACOMP] == 255) {
	    anyOne = 1;
	}
    }

    /* add in alphas */
    if (alpha0 == alpha1) {
	/* we'll use 6-vector */
	cc[0] = alpha0 | (alpha1 << 8);
	cc[1] = 0;
    } else {
	if (anyZero && ((alpha0 == 0) || (alpha1 == 0))) {
	    /* we still might use 8-vector */
	    anyZero = 0;
	}
	if (anyOne && ((alpha0 == 255) || (alpha1 == 255))) {
	    /* we still might use 8-vector */
	    anyOne = 0;
	}
	if ((anyZero | anyOne) ^ (alpha0 <= alpha1)) {
	    int aux;
	    aux = alpha0;
	    alpha0 = alpha1;
	    alpha1 = aux;
	}
	a_vect = (alpha0 <= alpha1) ? 5 : 7;

	/* compute interpolation vector */
	iv[ACOMP] = (float)a_vect / (alpha1 - alpha0);
	b = -iv[ACOMP] * alpha0 + 0.5F;

	/* add in alphas */
	Q_MOV32(lo, 0);
	for (k = N_TEXELS - 1; k >= 0; k--) {
	    int texel = -1;
	    if (anyZero | anyOne) {
		if (input[k][ACOMP] == 0) {
		    texel = 6;
		} else if (input[k][ACOMP] == 255) {
		    texel = 7;
		}
	    }
	    /* interpolate alpha */
	    if (texel == -1) {
		float dot = input[k][ACOMP] * iv[ACOMP];
		texel = (int)(dot + b);
#if SAFECDOT
		if (texel < 0) {
		    texel = 0;
		} else if (texel > a_vect) {
		    texel = a_vect;
		}
#endif
		texel = dxtn_alpha_tlat[anyZero | anyOne][texel];
	    }
	    /* add in texel */
	    Q_SHL(lo, 3);
	    Q_OR32(lo, texel);
	}
	Q_SHL(lo, 16);
	Q_OR32(lo, alpha0 | (alpha1 << 8));
	((qword *)cc)[0] = lo;
    }

    color0 = COLOR565(input[minCol]);
    color1 = COLOR565(input[maxCol]);

#ifdef RADEON /* H.Morii - Workaround for ATI Radeon */
    if (color0 < color1) {
	int aux;
	aux = color0;
	color0 = color1;
	color1 = aux;
	aux = minCol;
	minCol = maxCol;
	maxCol = aux;
    }
#endif

    cc[2] = color0 | (color1 << 16);

    hihi = 0;
    if (color0 != color1) {
	MAKEIVEC(n_vect, n_comp, iv, b, input[minCol], input[maxCol]);

	/* add in texels */
	for (k = N_TEXELS - 1; k >= 0; k--) {
	    int texel;
	    /* interpolate color */
	    CALCCDOT(texel, n_vect, n_comp, iv, b, input[k]);
	    texel = dxtn_color_tlat[0][texel];
	    /* add in texel */
	    hihi <<= 2;
	    hihi |= texel;
	}
    }
    cc[3] = hihi;
}