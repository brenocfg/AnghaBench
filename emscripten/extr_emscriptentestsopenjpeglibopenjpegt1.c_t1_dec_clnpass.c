#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int h; int w; int flags_stride; int* data; int /*<<< orphan*/ * flags; int /*<<< orphan*/ * mqc; } ;
typedef  TYPE_1__ opj_t1_t ;
typedef  int /*<<< orphan*/  opj_mqc_t ;
typedef  int /*<<< orphan*/  flag_t ;

/* Variables and functions */
 int J2K_CCP_CBLKSTY_SEGSYM ; 
 int J2K_CCP_CBLKSTY_VSC ; 
 int MACRO_t1_flags (int,int) ; 
 int /*<<< orphan*/  T1_CTXNO_AGG ; 
 int /*<<< orphan*/  T1_CTXNO_UNI ; 
 int T1_SGN_S ; 
 int T1_SIG ; 
 int T1_SIG_OTH ; 
 int T1_SIG_S ; 
 int T1_SIG_SE ; 
 int T1_SIG_SW ; 
 int T1_VISIT ; 
 int mqc_decode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mqc_setcurctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_dec_clnpass_step (TYPE_1__*,int /*<<< orphan*/ *,int*,int,int) ; 
 int /*<<< orphan*/  t1_dec_clnpass_step_partial (TYPE_1__*,int /*<<< orphan*/ *,int*,int,int) ; 
 int /*<<< orphan*/  t1_dec_clnpass_step_vsc (TYPE_1__*,int /*<<< orphan*/ *,int*,int,int,int,int) ; 

__attribute__((used)) static void t1_dec_clnpass(
		opj_t1_t *t1,
		int bpno,
		int orient,
		int cblksty)
{
	int i, j, k, one, half, oneplushalf, agg, runlen, vsc;
	int segsym = cblksty & J2K_CCP_CBLKSTY_SEGSYM;
	
	opj_mqc_t *mqc = t1->mqc;	/* MQC component */
	
	one = 1 << bpno;
	half = one >> 1;
	oneplushalf = one | half;
	if (cblksty & J2K_CCP_CBLKSTY_VSC) {
	for (k = 0; k < t1->h; k += 4) {
		for (i = 0; i < t1->w; ++i) {
			if (k + 3 < t1->h) {
					agg = !(MACRO_t1_flags(1 + k,1 + i) & (T1_SIG | T1_VISIT | T1_SIG_OTH)
						|| MACRO_t1_flags(1 + k + 1,1 + i) & (T1_SIG | T1_VISIT | T1_SIG_OTH)
						|| MACRO_t1_flags(1 + k + 2,1 + i) & (T1_SIG | T1_VISIT | T1_SIG_OTH)
						|| (MACRO_t1_flags(1 + k + 3,1 + i) 
						& (~(T1_SIG_S | T1_SIG_SE | T1_SIG_SW |	T1_SGN_S))) & (T1_SIG | T1_VISIT | T1_SIG_OTH));
				} else {
				agg = 0;
			}
			if (agg) {
				mqc_setcurctx(mqc, T1_CTXNO_AGG);
				if (!mqc_decode(mqc)) {
					continue;
				}
				mqc_setcurctx(mqc, T1_CTXNO_UNI);
				runlen = mqc_decode(mqc);
				runlen = (runlen << 1) | mqc_decode(mqc);
			} else {
				runlen = 0;
			}
			for (j = k + runlen; j < k + 4 && j < t1->h; ++j) {
					vsc = (j == k + 3 || j == t1->h - 1) ? 1 : 0;
					t1_dec_clnpass_step_vsc(
						t1,
						&t1->flags[((j+1) * t1->flags_stride) + i + 1],
						&t1->data[(j * t1->w) + i],
						orient,
						oneplushalf,
						agg && (j == k + runlen),
						vsc);
			}
		}
	}
	} else {
		int *data1 = t1->data;
		flag_t *flags1 = &t1->flags[1];
		for (k = 0; k < (t1->h & ~3); k += 4) {
			for (i = 0; i < t1->w; ++i) {
				int *data2 = data1 + i;
				flag_t *flags2 = flags1 + i;
				agg = !(MACRO_t1_flags(1 + k,1 + i) & (T1_SIG | T1_VISIT | T1_SIG_OTH)
					|| MACRO_t1_flags(1 + k + 1,1 + i) & (T1_SIG | T1_VISIT | T1_SIG_OTH)
					|| MACRO_t1_flags(1 + k + 2,1 + i) & (T1_SIG | T1_VISIT | T1_SIG_OTH)
					|| MACRO_t1_flags(1 + k + 3,1 + i) & (T1_SIG | T1_VISIT | T1_SIG_OTH));
				if (agg) {
					mqc_setcurctx(mqc, T1_CTXNO_AGG);
					if (!mqc_decode(mqc)) {
						continue;
					}
					mqc_setcurctx(mqc, T1_CTXNO_UNI);
					runlen = mqc_decode(mqc);
					runlen = (runlen << 1) | mqc_decode(mqc);
					flags2 += runlen * t1->flags_stride;
					data2 += runlen * t1->w;
					for (j = k + runlen; j < k + 4 && j < t1->h; ++j) {
						flags2 += t1->flags_stride;
						if (agg && (j == k + runlen)) {
							t1_dec_clnpass_step_partial(t1, flags2, data2, orient, oneplushalf);
						} else {
							t1_dec_clnpass_step(t1, flags2, data2, orient, oneplushalf);
						}
						data2 += t1->w;
					}
				} else {
					flags2 += t1->flags_stride;
					t1_dec_clnpass_step(t1, flags2, data2, orient, oneplushalf);
					data2 += t1->w;
					flags2 += t1->flags_stride;
					t1_dec_clnpass_step(t1, flags2, data2, orient, oneplushalf);
					data2 += t1->w;
					flags2 += t1->flags_stride;
					t1_dec_clnpass_step(t1, flags2, data2, orient, oneplushalf);
					data2 += t1->w;
					flags2 += t1->flags_stride;
					t1_dec_clnpass_step(t1, flags2, data2, orient, oneplushalf);
					data2 += t1->w;
				}
			}
			data1 += t1->w << 2;
			flags1 += t1->flags_stride << 2;
		}
		for (i = 0; i < t1->w; ++i) {
			int *data2 = data1 + i;
			flag_t *flags2 = flags1 + i;
			for (j = k; j < t1->h; ++j) {
				flags2 += t1->flags_stride;
				t1_dec_clnpass_step(t1, flags2, data2, orient, oneplushalf);
				data2 += t1->w;
			}
		}
	}

	if (segsym) {
		int v = 0;
		mqc_setcurctx(mqc, T1_CTXNO_UNI);
		v = mqc_decode(mqc);
		v = (v << 1) | mqc_decode(mqc);
		v = (v << 1) | mqc_decode(mqc);
		v = (v << 1) | mqc_decode(mqc);
		/*
		if (v!=0xa) {
			opj_event_msg(t1->cinfo, EVT_WARNING, "Bad segmentation symbol %x\n", v);
		} 
		*/
	}
}