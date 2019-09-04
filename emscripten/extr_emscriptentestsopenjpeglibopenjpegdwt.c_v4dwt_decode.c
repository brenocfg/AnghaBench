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
struct TYPE_3__ {scalar_t__ cas; int dn; int sn; scalar_t__ wavelet; } ;
typedef  TYPE_1__ v4dwt_t ;

/* Variables and functions */
 int /*<<< orphan*/  K ; 
 int /*<<< orphan*/  _mm_set1_ps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c13318 ; 
 int /*<<< orphan*/  dwt_alpha ; 
 int /*<<< orphan*/  dwt_beta ; 
 int /*<<< orphan*/  dwt_delta ; 
 int /*<<< orphan*/  dwt_gamma ; 
 int /*<<< orphan*/  int_min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4dwt_decode_step1_sse (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4dwt_decode_step2_sse (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void v4dwt_decode(v4dwt_t* restrict dwt){
	int a, b;
	if(dwt->cas == 0) {
		if(!((dwt->dn > 0) || (dwt->sn > 1))){
			return;
		}
		a = 0;
		b = 1;
	}else{
		if(!((dwt->sn > 0) || (dwt->dn > 1))) {
			return;
		}
		a = 1;
		b = 0;
	}
#ifdef __SSE__
	v4dwt_decode_step1_sse(dwt->wavelet+a, dwt->sn, _mm_set1_ps(K));
	v4dwt_decode_step1_sse(dwt->wavelet+b, dwt->dn, _mm_set1_ps(c13318));
	v4dwt_decode_step2_sse(dwt->wavelet+b, dwt->wavelet+a+1, dwt->sn, int_min(dwt->sn, dwt->dn-a), _mm_set1_ps(dwt_delta));
	v4dwt_decode_step2_sse(dwt->wavelet+a, dwt->wavelet+b+1, dwt->dn, int_min(dwt->dn, dwt->sn-b), _mm_set1_ps(dwt_gamma));
	v4dwt_decode_step2_sse(dwt->wavelet+b, dwt->wavelet+a+1, dwt->sn, int_min(dwt->sn, dwt->dn-a), _mm_set1_ps(dwt_beta));
	v4dwt_decode_step2_sse(dwt->wavelet+a, dwt->wavelet+b+1, dwt->dn, int_min(dwt->dn, dwt->sn-b), _mm_set1_ps(dwt_alpha));
#else
	v4dwt_decode_step1(dwt->wavelet+a, dwt->sn, K);
	v4dwt_decode_step1(dwt->wavelet+b, dwt->dn, c13318);
	v4dwt_decode_step2(dwt->wavelet+b, dwt->wavelet+a+1, dwt->sn, int_min(dwt->sn, dwt->dn-a), dwt_delta);
	v4dwt_decode_step2(dwt->wavelet+a, dwt->wavelet+b+1, dwt->dn, int_min(dwt->dn, dwt->sn-b), dwt_gamma);
	v4dwt_decode_step2(dwt->wavelet+b, dwt->wavelet+a+1, dwt->sn, int_min(dwt->sn, dwt->dn-a), dwt_beta);
	v4dwt_decode_step2(dwt->wavelet+a, dwt->wavelet+b+1, dwt->dn, int_min(dwt->dn, dwt->sn-b), dwt_alpha);
#endif
}