#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int sn; int dn; int cas; TYPE_2__* wavelet; } ;
typedef  TYPE_1__ v4dwt_t ;
struct TYPE_13__ {float* f; } ;
typedef  TYPE_2__ v4 ;
struct TYPE_14__ {int x1; int x0; int y1; int y0; scalar_t__ data; TYPE_4__* resolutions; } ;
typedef  TYPE_3__ opj_tcd_tilecomp_t ;
struct TYPE_15__ {int x1; int x0; int y1; int y0; } ;
typedef  TYPE_4__ opj_tcd_resolution_t ;

/* Variables and functions */
 int dwt_decode_max_resolution (TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcpy (float*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  opj_aligned_free (TYPE_2__*) ; 
 scalar_t__ opj_aligned_malloc (int) ; 
 int /*<<< orphan*/  v4dwt_decode (TYPE_1__*) ; 
 int /*<<< orphan*/  v4dwt_interleave_h (TYPE_1__*,float*,int,int) ; 
 int /*<<< orphan*/  v4dwt_interleave_v (TYPE_1__*,float*,int) ; 

void dwt_decode_real(opj_tcd_tilecomp_t* restrict tilec, int numres){
	v4dwt_t h;
	v4dwt_t v;

	opj_tcd_resolution_t* res = tilec->resolutions;

	int rw = res->x1 - res->x0;	/* width of the resolution level computed */
	int rh = res->y1 - res->y0;	/* height of the resolution level computed */

	int w = tilec->x1 - tilec->x0;

	h.wavelet = (v4*) opj_aligned_malloc((dwt_decode_max_resolution(res, numres)+5) * sizeof(v4));
	v.wavelet = h.wavelet;

	while( --numres) {
		float * restrict aj = (float*) tilec->data;
		int bufsize = (tilec->x1 - tilec->x0) * (tilec->y1 - tilec->y0);
		int j;

		h.sn = rw;
		v.sn = rh;

		++res;

		rw = res->x1 - res->x0;	/* width of the resolution level computed */
		rh = res->y1 - res->y0;	/* height of the resolution level computed */

		h.dn = rw - h.sn;
		h.cas = res->x0 % 2;

		for(j = rh; j > 3; j -= 4){
			int k;
			v4dwt_interleave_h(&h, aj, w, bufsize);
			v4dwt_decode(&h);
				for(k = rw; --k >= 0;){
					aj[k    ] = h.wavelet[k].f[0];
					aj[k+w  ] = h.wavelet[k].f[1];
					aj[k+w*2] = h.wavelet[k].f[2];
					aj[k+w*3] = h.wavelet[k].f[3];
				}
			aj += w*4;
			bufsize -= w*4;
		}
		if (rh & 0x03) {
				int k;
			j = rh & 0x03;
			v4dwt_interleave_h(&h, aj, w, bufsize);
			v4dwt_decode(&h);
				for(k = rw; --k >= 0;){
					switch(j) {
						case 3: aj[k+w*2] = h.wavelet[k].f[2];
						case 2: aj[k+w  ] = h.wavelet[k].f[1];
						case 1: aj[k    ] = h.wavelet[k].f[0];
					}
				}
			}

		v.dn = rh - v.sn;
		v.cas = res->y0 % 2;

		aj = (float*) tilec->data;
		for(j = rw; j > 3; j -= 4){
			int k;
			v4dwt_interleave_v(&v, aj, w);
			v4dwt_decode(&v);
				for(k = 0; k < rh; ++k){
					memcpy(&aj[k*w], &v.wavelet[k], 4 * sizeof(float));
				}
			aj += 4;
		}
		if (rw & 0x03){
				int k;
			j = rw & 0x03;
			v4dwt_interleave_v(&v, aj, w);
			v4dwt_decode(&v);
				for(k = 0; k < rh; ++k){
					memcpy(&aj[k*w], &v.wavelet[k], j * sizeof(float));
				}
			}
	}

	opj_aligned_free(h.wavelet);
}