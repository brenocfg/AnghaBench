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
 int ALPHA_TS ; 
 int /*<<< orphan*/  COPY_4UBV (int*,int*) ; 
 int /*<<< orphan*/  ISTBLACK (int*) ; 
 int MAX_COMP ; 
 int N_TEXELS ; 
 int /*<<< orphan*/  fxt1_quantize_ALPHA0 (int*,int**,int**,int) ; 
 int /*<<< orphan*/  fxt1_quantize_ALPHA1 (int*,int**) ; 
 int /*<<< orphan*/  fxt1_quantize_CHROMA (int*,int**) ; 
 int /*<<< orphan*/  fxt1_quantize_HI (int*,int**,int**,int) ; 
 int /*<<< orphan*/  fxt1_quantize_MIXED0 (int*,int**) ; 
 int /*<<< orphan*/  fxt1_quantize_MIXED1 (int*,int**) ; 
 int /*<<< orphan*/  memset (int**,int,int) ; 

__attribute__((used)) static void
fxt1_quantize (dword *cc, const byte *lines[], int comps)
{
    int trualpha;
    byte reord[N_TEXELS][MAX_COMP];

    byte input[N_TEXELS][MAX_COMP];
#ifndef ARGB
    int i;
#endif
    int k, l;

    if (comps == 3) {
	/* make the whole block opaque */
	memset(input, -1, sizeof(input));
    }

    /* 8 texels each line */
#ifndef ARGB
    for (l = 0; l < 4; l++) {
	for (k = 0; k < 4; k++) {
	    for (i = 0; i < comps; i++) {
		input[k + l * 4][i] = *lines[l]++;
	    }
	}
	for (; k < 8; k++) {
	    for (i = 0; i < comps; i++) {
		input[k + l * 4 + 12][i] = *lines[l]++;
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
	for (; k < 8; k++) {
          input[k + l * 4 + 12][2] = *lines[l]++;
          input[k + l * 4 + 12][1] = *lines[l]++;
          input[k + l * 4 + 12][0] = *lines[l]++;
          if (comps == 4) input[k + l * 4 + 12][3] = *lines[l]++;
	}
    }
#endif

    /* block layout:
     * 00, 01, 02, 03, 08, 09, 0a, 0b
     * 10, 11, 12, 13, 18, 19, 1a, 1b
     * 04, 05, 06, 07, 0c, 0d, 0e, 0f
     * 14, 15, 16, 17, 1c, 1d, 1e, 1f
     */

    /* [dBorca]
     * stupidity flows forth from this
     */
    l = N_TEXELS;
    trualpha = 0;
    if (comps == 4) {
	/* skip all transparent black texels */
	l = 0;
	for (k = 0; k < N_TEXELS; k++) {
	    /* test all components against 0 */
	    if (!ISTBLACK(input[k])) {
		/* texel is not transparent black */
		COPY_4UBV(reord[l], input[k]);
		if (reord[l][ACOMP] < (255 - ALPHA_TS)) {
		    /* non-opaque texel */
		    trualpha = !0;
		}
		l++;
	    }
	}
    }

#if 0
    if (trualpha) {
	fxt1_quantize_ALPHA0(cc, input, reord, l);
    } else if (l == 0) {
	cc[0] = cc[1] = cc[2] = -1;
	cc[3] = 0;
    } else if (l < N_TEXELS) {
	fxt1_quantize_HI(cc, input, reord, l);
    } else {
	fxt1_quantize_CHROMA(cc, input);
    }
    (void)fxt1_quantize_ALPHA1;
    (void)fxt1_quantize_MIXED1;
    (void)fxt1_quantize_MIXED0;
#else
    if (trualpha) {
	fxt1_quantize_ALPHA1(cc, input);
    } else if (l == 0) {
	cc[0] = cc[1] = cc[2] = 0xFFFFFFFF;
	cc[3] = 0;
    } else if (l < N_TEXELS) {
	fxt1_quantize_MIXED1(cc, input);
    } else {
	fxt1_quantize_MIXED0(cc, input);
    }
    (void)fxt1_quantize_ALPHA0;
    (void)fxt1_quantize_HI;
    (void)fxt1_quantize_CHROMA;
#endif
}