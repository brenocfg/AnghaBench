#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int h; int w; int flags_stride; int /*<<< orphan*/ * data; int /*<<< orphan*/ * flags; int /*<<< orphan*/ * mqc; } ;
typedef  TYPE_1__ opj_t1_t ;
typedef  int /*<<< orphan*/  opj_mqc_t ;

/* Variables and functions */
 int J2K_CCP_CBLKSTY_VSC ; 
 int MACRO_t1_flags (int,int) ; 
 int /*<<< orphan*/  T1_CTXNO_AGG ; 
 int /*<<< orphan*/  T1_CTXNO_UNI ; 
 int T1_NMSEDEC_FRACBITS ; 
 int T1_SGN_S ; 
 int T1_SIG ; 
 int T1_SIG_OTH ; 
 int T1_SIG_S ; 
 int T1_SIG_SE ; 
 int T1_SIG_SW ; 
 int T1_VISIT ; 
 int int_abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mqc_encode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mqc_setcurctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_enc_clnpass_step (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int*,int,int) ; 

__attribute__((used)) static void t1_enc_clnpass(
		opj_t1_t *t1,
		int bpno,
		int orient,
		int *nmsedec,
		int cblksty)
{
	int i, j, k, one, agg, runlen, vsc;
	
	opj_mqc_t *mqc = t1->mqc;	/* MQC component */
	
	*nmsedec = 0;
	one = 1 << (bpno + T1_NMSEDEC_FRACBITS);
	for (k = 0; k < t1->h; k += 4) {
		for (i = 0; i < t1->w; ++i) {
			if (k + 3 < t1->h) {
				if (cblksty & J2K_CCP_CBLKSTY_VSC) {
					agg = !(MACRO_t1_flags(1 + k,1 + i) & (T1_SIG | T1_VISIT | T1_SIG_OTH)
						|| MACRO_t1_flags(1 + k + 1,1 + i) & (T1_SIG | T1_VISIT | T1_SIG_OTH)
						|| MACRO_t1_flags(1 + k + 2,1 + i) & (T1_SIG | T1_VISIT | T1_SIG_OTH)
						|| (MACRO_t1_flags(1 + k + 3,1 + i) 
						& (~(T1_SIG_S | T1_SIG_SE | T1_SIG_SW |	T1_SGN_S))) & (T1_SIG | T1_VISIT | T1_SIG_OTH));
				} else {
					agg = !(MACRO_t1_flags(1 + k,1 + i) & (T1_SIG | T1_VISIT | T1_SIG_OTH)
						|| MACRO_t1_flags(1 + k + 1,1 + i) & (T1_SIG | T1_VISIT | T1_SIG_OTH)
						|| MACRO_t1_flags(1 + k + 2,1 + i) & (T1_SIG | T1_VISIT | T1_SIG_OTH)
						|| MACRO_t1_flags(1 + k + 3,1 + i) & (T1_SIG | T1_VISIT | T1_SIG_OTH));
				}
			} else {
				agg = 0;
			}
			if (agg) {
				for (runlen = 0; runlen < 4; ++runlen) {
					if (int_abs(t1->data[((k + runlen)*t1->w) + i]) & one)
						break;
				}
				mqc_setcurctx(mqc, T1_CTXNO_AGG);
				mqc_encode(mqc, runlen != 4);
				if (runlen == 4) {
					continue;
				}
				mqc_setcurctx(mqc, T1_CTXNO_UNI);
				mqc_encode(mqc, runlen >> 1);
				mqc_encode(mqc, runlen & 1);
			} else {
				runlen = 0;
			}
			for (j = k + runlen; j < k + 4 && j < t1->h; ++j) {
				vsc = ((cblksty & J2K_CCP_CBLKSTY_VSC) && (j == k + 3 || j == t1->h - 1)) ? 1 : 0;
				t1_enc_clnpass_step(
						t1,
						&t1->flags[((j+1) * t1->flags_stride) + i + 1],
						&t1->data[(j * t1->w) + i],
						orient,
						bpno,
						one,
						nmsedec,
						agg && (j == k + runlen),
						vsc);
			}
		}
	}
}