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
typedef  int /*<<< orphan*/  input ;
typedef  int dword ;
typedef  int byte ;

/* Variables and functions */
 size_t ACOMP ; 
 size_t BCOMP ; 
 int /*<<< orphan*/  CALCCDOT (int,int,int const,float*,float,int*) ; 
 int COLOR565 (int*) ; 
 size_t GCOMP ; 
 int /*<<< orphan*/  MAKEIVEC (int,int const,float*,float,int*,int*) ; 
 int MAX_COMP ; 
 int N_TEXELS ; 
 size_t RCOMP ; 
 int** dxtn_color_tlat ; 
 int /*<<< orphan*/  memset (int**,int,int) ; 

__attribute__((used)) static void
dxt1_rgba_quantize (dword *cc, const byte *lines[], int comps)
{
    float b, iv[MAX_COMP];	/* interpolation vector */

    dword hi;		/* high doubleword */
    int color0, color1;
    int n_vect;
    const int n_comp = 3;
    int transparent = 0;

#ifndef YUV
    int minSum = 2000;          /* big enough */
#else
    int minSum = 2000000;
#endif
    int maxSum = -1;		/* small enough */
    int minCol = 0;		/* phoudoin: silent compiler! */
    int maxCol = 0;		/* phoudoin: silent compiler! */

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
	if (input[k][ACOMP] < 128) {
	    transparent = 1;
	}
    }

    color0 = COLOR565(input[minCol]);
    color1 = COLOR565(input[maxCol]);

    if (color0 == color1) {
	/* we'll use 3-vector */
	cc[0] = color0 | (color1 << 16);
	hi = transparent ? -1 : 0;
    } else {
	if (transparent ^ (color0 <= color1)) {
	    int aux;
	    aux = color0;
	    color0 = color1;
	    color1 = aux;
	    aux = minCol;
	    minCol = maxCol;
	    maxCol = aux;
	}
	n_vect = (color0 <= color1) ? 2 : 3;

	MAKEIVEC(n_vect, n_comp, iv, b, input[minCol], input[maxCol]);

	/* add in texels */
	cc[0] = color0 | (color1 << 16);
	hi = 0;
	for (k = N_TEXELS - 1; k >= 0; k--) {
	    int texel = 3;
	    if (input[k][ACOMP] >= 128) {
		/* interpolate color */
		CALCCDOT(texel, n_vect, n_comp, iv, b, input[k]);
		texel = dxtn_color_tlat[transparent][texel];
	    }
	    /* add in texel */
	    hi <<= 2;
	    hi |= texel;
	}
    }
    cc[1] = hi;
}