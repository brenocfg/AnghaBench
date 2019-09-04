#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* tccps; } ;
typedef  TYPE_2__ opj_tcp_t ;
struct TYPE_9__ {int qntsty; int numgbits; TYPE_1__* stepsizes; } ;
typedef  TYPE_3__ opj_tccp_t ;
struct TYPE_10__ {scalar_t__ state; size_t curtileno; int /*<<< orphan*/ * cio; TYPE_2__* default_tcp; TYPE_5__* cp; } ;
typedef  TYPE_4__ opj_j2k_t ;
struct TYPE_11__ {TYPE_2__* tcps; } ;
typedef  TYPE_5__ opj_cp_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_7__ {int expn; int mant; } ;

/* Variables and functions */
 int J2K_CCP_QNTSTY_NOQNT ; 
 int J2K_CCP_QNTSTY_SIQNT ; 
 int J2K_MAXBANDS ; 
 scalar_t__ J2K_STATE_TPH ; 
 int cio_read (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void j2k_read_qcx(opj_j2k_t *j2k, int compno, int len) {
	int tmp;
	int bandno, numbands;

	opj_cp_t *cp = j2k->cp;
	opj_tcp_t *tcp = j2k->state == J2K_STATE_TPH ? &cp->tcps[j2k->curtileno] : j2k->default_tcp;
	opj_tccp_t *tccp = &tcp->tccps[compno];
	opj_cio_t *cio = j2k->cio;

	tmp = cio_read(cio, 1);		/* Sqcx */
	tccp->qntsty = tmp & 0x1f;
	tccp->numgbits = tmp >> 5;
	numbands = (tccp->qntsty == J2K_CCP_QNTSTY_SIQNT) ? 
		1 : ((tccp->qntsty == J2K_CCP_QNTSTY_NOQNT) ? len - 1 : (len - 1) / 2);

#ifdef USE_JPWL
	if (j2k->cp->correct) {

		/* if JPWL is on, we check whether there are too many subbands */
		if ((numbands < 0) || (numbands >= J2K_MAXBANDS)) {
			opj_event_msg(j2k->cinfo, JPWL_ASSUME ? EVT_WARNING : EVT_ERROR,
				"JPWL: bad number of subbands in Sqcx (%d)\n",
				numbands);
			if (!JPWL_ASSUME) {
				opj_event_msg(j2k->cinfo, EVT_ERROR, "JPWL: giving up\n");
				return;
			}
			/* we try to correct */
			numbands = 1;
			opj_event_msg(j2k->cinfo, EVT_WARNING, "- trying to adjust them\n"
				"- setting number of bands to %d => HYPOTHESIS!!!\n",
				numbands);
		};

	};
#endif /* USE_JPWL */

	for (bandno = 0; bandno < numbands; bandno++) {
		int expn, mant;
		if (tccp->qntsty == J2K_CCP_QNTSTY_NOQNT) {
			expn = cio_read(cio, 1) >> 3;	/* SPqcx_i */
			mant = 0;
		} else {
			tmp = cio_read(cio, 2);	/* SPqcx_i */
			expn = tmp >> 11;
			mant = tmp & 0x7ff;
		}
		tccp->stepsizes[bandno].expn = expn;
		tccp->stepsizes[bandno].mant = mant;
	}
	
	/* Add Antonin : if scalar_derived -> compute other stepsizes */
	if (tccp->qntsty == J2K_CCP_QNTSTY_SIQNT) {
		for (bandno = 1; bandno < J2K_MAXBANDS; bandno++) {
			tccp->stepsizes[bandno].expn = 
				((tccp->stepsizes[0].expn) - ((bandno - 1) / 3) > 0) ? 
					(tccp->stepsizes[0].expn) - ((bandno - 1) / 3) : 0;
			tccp->stepsizes[bandno].mant = tccp->stepsizes[0].mant;
		}
	}
	/* ddA */
}