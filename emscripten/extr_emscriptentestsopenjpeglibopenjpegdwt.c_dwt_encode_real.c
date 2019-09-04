#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int x1; int x0; int numresolutions; int* data; TYPE_1__* resolutions; } ;
typedef  TYPE_2__ opj_tcd_tilecomp_t ;
struct TYPE_4__ {int x1; int x0; int y1; int y0; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwt_deinterleave_h (int*,int*,int,int,int) ; 
 int /*<<< orphan*/  dwt_deinterleave_v (int*,int*,int,int,int,int) ; 
 int /*<<< orphan*/  dwt_encode_1_real (int*,int,int,int) ; 
 int /*<<< orphan*/  opj_free (int*) ; 
 scalar_t__ opj_malloc (int) ; 

void dwt_encode_real(opj_tcd_tilecomp_t * tilec) {
	int i, j, k;
	int *a = NULL;
	int *aj = NULL;
	int *bj = NULL;
	int w, l;
	
	w = tilec->x1-tilec->x0;
	l = tilec->numresolutions-1;
	a = tilec->data;
	
	for (i = 0; i < l; i++) {
		int rw;			/* width of the resolution level computed                                                     */
		int rh;			/* height of the resolution level computed                                                    */
		int rw1;		/* width of the resolution level once lower than computed one                                 */
		int rh1;		/* height of the resolution level once lower than computed one                                */
		int cas_col;	/* 0 = non inversion on horizontal filtering 1 = inversion between low-pass and high-pass filtering */
		int cas_row;	/* 0 = non inversion on vertical filtering 1 = inversion between low-pass and high-pass filtering   */
		int dn, sn;
		
		rw = tilec->resolutions[l - i].x1 - tilec->resolutions[l - i].x0;
		rh = tilec->resolutions[l - i].y1 - tilec->resolutions[l - i].y0;
		rw1= tilec->resolutions[l - i - 1].x1 - tilec->resolutions[l - i - 1].x0;
		rh1= tilec->resolutions[l - i - 1].y1 - tilec->resolutions[l - i - 1].y0;
		
		cas_row = tilec->resolutions[l - i].x0 % 2;
		cas_col = tilec->resolutions[l - i].y0 % 2;
		
		sn = rh1;
		dn = rh - rh1;
		bj = (int*)opj_malloc(rh * sizeof(int));
		for (j = 0; j < rw; j++) {
			aj = a + j;
			for (k = 0; k < rh; k++)  bj[k] = aj[k*w];
			dwt_encode_1_real(bj, dn, sn, cas_col);
			dwt_deinterleave_v(bj, aj, dn, sn, w, cas_col);
		}
		opj_free(bj);
		
		sn = rw1;
		dn = rw - rw1;
		bj = (int*)opj_malloc(rw * sizeof(int));
		for (j = 0; j < rh; j++) {
			aj = a + j * w;
			for (k = 0; k < rw; k++)  bj[k] = aj[k];
			dwt_encode_1_real(bj, dn, sn, cas_row);
			dwt_deinterleave_h(bj, aj, dn, sn, cas_row);
		}
		opj_free(bj);
	}
}