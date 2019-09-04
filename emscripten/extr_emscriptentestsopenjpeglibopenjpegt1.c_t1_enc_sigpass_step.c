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
struct TYPE_3__ {int /*<<< orphan*/  flags_stride; int /*<<< orphan*/ * mqc; } ;
typedef  TYPE_1__ opj_t1_t ;
typedef  int /*<<< orphan*/  opj_mqc_t ;
typedef  int flag_t ;

/* Variables and functions */
 scalar_t__ T1_NMSEDEC_FRACBITS ; 
 int T1_SGN_S ; 
 int T1_SIG ; 
 int T1_SIG_OTH ; 
 int T1_SIG_S ; 
 int T1_SIG_SE ; 
 int T1_SIG_SW ; 
 char T1_TYPE_RAW ; 
 int T1_VISIT ; 
 int int_abs (int) ; 
 int /*<<< orphan*/  mqc_bypass_enc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mqc_encode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mqc_setcurctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_getctxno_sc (int) ; 
 int /*<<< orphan*/  t1_getctxno_zc (int,int) ; 
 scalar_t__ t1_getnmsedec_sig (int,scalar_t__) ; 
 int t1_getspb (int) ; 
 int /*<<< orphan*/  t1_updateflags (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void t1_enc_sigpass_step(
		opj_t1_t *t1,
		flag_t *flagsp,
		int *datap,
		int orient,
		int bpno,
		int one,
		int *nmsedec,
		char type,
		int vsc)
{
	int v, flag;
	
	opj_mqc_t *mqc = t1->mqc;	/* MQC component */
	
	flag = vsc ? ((*flagsp) & (~(T1_SIG_S | T1_SIG_SE | T1_SIG_SW | T1_SGN_S))) : (*flagsp);
	if ((flag & T1_SIG_OTH) && !(flag & (T1_SIG | T1_VISIT))) {
		v = int_abs(*datap) & one ? 1 : 0;
		mqc_setcurctx(mqc, t1_getctxno_zc(flag, orient));	/* ESSAI */
		if (type == T1_TYPE_RAW) {	/* BYPASS/LAZY MODE */
			mqc_bypass_enc(mqc, v);
		} else {
			mqc_encode(mqc, v);
		}
		if (v) {
			v = *datap < 0 ? 1 : 0;
			*nmsedec +=	t1_getnmsedec_sig(int_abs(*datap), bpno + T1_NMSEDEC_FRACBITS);
			mqc_setcurctx(mqc, t1_getctxno_sc(flag));	/* ESSAI */
			if (type == T1_TYPE_RAW) {	/* BYPASS/LAZY MODE */
				mqc_bypass_enc(mqc, v);
			} else {
				mqc_encode(mqc, v ^ t1_getspb(flag));
			}
			t1_updateflags(flagsp, v, t1->flags_stride);
		}
		*flagsp |= T1_VISIT;
	}
}