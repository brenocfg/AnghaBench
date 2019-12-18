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
 int /*<<< orphan*/  CALCCDOT (int,int const,int const,float*,float,int*) ; 
 int COLOR565 (int*) ; 
 size_t GCOMP ; 
 int /*<<< orphan*/  MAKEIVEC (int const,int const,float*,float,int*,int*) ; 
 int MAX_COMP ; 
 int N_TEXELS ; 
 size_t RCOMP ; 
 int** dxtn_color_tlat ; 
 int /*<<< orphan*/  memset (int**,int,int) ; 

__attribute__((used)) static void
dxt3_rgba_quantize (dword *cc, const byte *lines[], int comps)
{
    float b, iv[MAX_COMP];	/* interpolation vector */

    dword lolo, lohi;	/* low quadword: lo dword, hi dword */
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
    }

    /* add in alphas */
    lolo = lohi = 0;
    for (k = N_TEXELS - 1; k >= N_TEXELS / 2; k--) {
	/* add in alpha */
	lohi <<= 4;
	lohi |= input[k][ACOMP] >> 4;
    }
    cc[1] = lohi;
    for (; k >= 0; k--) {
	/* add in alpha */
	lolo <<= 4;
	lolo |= input[k][ACOMP] >> 4;
    }
    cc[0] = lolo;

    color0 = COLOR565(input[minCol]);
    color1 = COLOR565(input[maxCol]);

#ifdef RADEON
    /* H.Morii - Workaround for ATI Radeon
     * According to the OpenGL EXT_texture_compression_s3tc specs,
     * the encoding of the RGB components for DXT3 and DXT5 formats
     * use the non-transparent encodings of DXT1 but treated as
     * though color0 > color1, regardless of the actual values of
     * color0 and color1. ATI Radeons however require the values to
     * be color0 > color1.
     */
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