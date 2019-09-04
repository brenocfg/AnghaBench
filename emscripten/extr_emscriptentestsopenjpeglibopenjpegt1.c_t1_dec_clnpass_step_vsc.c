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
 int T1_SGN_S ; 
 int T1_SIG ; 
 int T1_SIG_S ; 
 int T1_SIG_SE ; 
 int T1_SIG_SW ; 
 int T1_VISIT ; 
 int mqc_decode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mqc_setcurctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_getctxno_sc (int) ; 
 int /*<<< orphan*/  t1_getctxno_zc (int,int) ; 
 int t1_getspb (int) ; 
 int /*<<< orphan*/  t1_updateflags (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void t1_dec_clnpass_step_vsc(
		opj_t1_t *t1,
		flag_t *flagsp,
		int *datap,
		int orient,
		int oneplushalf,
		int partial,
		int vsc)
{
	int v, flag;
	
	opj_mqc_t *mqc = t1->mqc;	/* MQC component */
	
	flag = vsc ? ((*flagsp) & (~(T1_SIG_S | T1_SIG_SE | T1_SIG_SW | T1_SGN_S))) : (*flagsp);
	if (partial) {
		goto LABEL_PARTIAL;
	}
	if (!(flag & (T1_SIG | T1_VISIT))) {
		mqc_setcurctx(mqc, t1_getctxno_zc(flag, orient));
		if (mqc_decode(mqc)) {
LABEL_PARTIAL:
			mqc_setcurctx(mqc, t1_getctxno_sc(flag));
			v = mqc_decode(mqc) ^ t1_getspb(flag);
			*datap = v ? -oneplushalf : oneplushalf;
			t1_updateflags(flagsp, v, t1->flags_stride);
		}
	}
	*flagsp &= ~T1_VISIT;
}