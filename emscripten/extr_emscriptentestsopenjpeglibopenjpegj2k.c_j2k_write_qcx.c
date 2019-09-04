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
struct TYPE_9__ {int qntsty; int numgbits; int numresolutions; TYPE_1__* stepsizes; } ;
typedef  TYPE_3__ opj_tccp_t ;
struct TYPE_10__ {size_t curtileno; int /*<<< orphan*/ * cio; TYPE_5__* cp; } ;
typedef  TYPE_4__ opj_j2k_t ;
struct TYPE_11__ {TYPE_2__* tcps; } ;
typedef  TYPE_5__ opj_cp_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_7__ {int expn; int mant; } ;

/* Variables and functions */
 scalar_t__ J2K_CCP_QNTSTY_NOQNT ; 
 scalar_t__ J2K_CCP_QNTSTY_SIQNT ; 
 int /*<<< orphan*/  cio_write (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void j2k_write_qcx(opj_j2k_t *j2k, int compno) {
	int bandno, numbands;
	int expn, mant;
	
	opj_cp_t *cp = j2k->cp;
	opj_tcp_t *tcp = &cp->tcps[j2k->curtileno];
	opj_tccp_t *tccp = &tcp->tccps[compno];
	opj_cio_t *cio = j2k->cio;
	
	cio_write(cio, tccp->qntsty + (tccp->numgbits << 5), 1);	/* Sqcx */
	numbands = tccp->qntsty == J2K_CCP_QNTSTY_SIQNT ? 1 : tccp->numresolutions * 3 - 2;
	
	for (bandno = 0; bandno < numbands; bandno++) {
		expn = tccp->stepsizes[bandno].expn;
		mant = tccp->stepsizes[bandno].mant;
		
		if (tccp->qntsty == J2K_CCP_QNTSTY_NOQNT) {
			cio_write(cio, expn << 3, 1);	/* SPqcx_i */
		} else {
			cio_write(cio, (expn << 11) + mant, 2);	/* SPqcx_i */
		}
	}
}