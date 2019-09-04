#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sn; int dn; scalar_t__ cas; scalar_t__ wavelet; } ;
typedef  TYPE_1__ v4dwt_t ;

/* Variables and functions */

__attribute__((used)) static void v4dwt_interleave_h(v4dwt_t* restrict w, float* restrict a, int x, int size){
	float* restrict bi = (float*) (w->wavelet + w->cas);
	int count = w->sn;
	int i, k;
	for(k = 0; k < 2; ++k){
		if (count + 3 * x < size && ((int) a & 0x0f) == 0 && ((int) bi & 0x0f) == 0 && (x & 0x0f) == 0) {
			/* Fast code path */
			for(i = 0; i < count; ++i){
				int j = i;
				bi[i*8    ] = a[j];
				j += x;
				bi[i*8 + 1] = a[j];
				j += x;
				bi[i*8 + 2] = a[j];
				j += x;
				bi[i*8 + 3] = a[j];
			}
		} else {
			/* Slow code path */
		for(i = 0; i < count; ++i){
			int j = i;
			bi[i*8    ] = a[j];
			j += x;
			if(j > size) continue;
			bi[i*8 + 1] = a[j];
			j += x;
			if(j > size) continue;
			bi[i*8 + 2] = a[j];
			j += x;
			if(j > size) continue;
			bi[i*8 + 3] = a[j];
		}
		}
		bi = (float*) (w->wavelet + 1 - w->cas);
		a += w->sn;
		size -= w->sn;
		count = w->dn;
	}
}