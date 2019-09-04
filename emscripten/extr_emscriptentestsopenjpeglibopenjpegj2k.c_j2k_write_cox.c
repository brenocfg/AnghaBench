#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* tccps; } ;
typedef  TYPE_1__ opj_tcp_t ;
struct TYPE_7__ {int numresolutions; int cblkw; int cblkh; int cblksty; int qmfbid; int csty; int* prcw; int* prch; } ;
typedef  TYPE_2__ opj_tccp_t ;
struct TYPE_8__ {size_t curtileno; int /*<<< orphan*/ * cio; TYPE_4__* cp; } ;
typedef  TYPE_3__ opj_j2k_t ;
struct TYPE_9__ {TYPE_1__* tcps; } ;
typedef  TYPE_4__ opj_cp_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 int J2K_CCP_CSTY_PRT ; 
 int /*<<< orphan*/  cio_write (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void j2k_write_cox(opj_j2k_t *j2k, int compno) {
	int i;

	opj_cp_t *cp = j2k->cp;
	opj_tcp_t *tcp = &cp->tcps[j2k->curtileno];
	opj_tccp_t *tccp = &tcp->tccps[compno];
	opj_cio_t *cio = j2k->cio;
	
	cio_write(cio, tccp->numresolutions - 1, 1);	/* SPcox (D) */
	cio_write(cio, tccp->cblkw - 2, 1);				/* SPcox (E) */
	cio_write(cio, tccp->cblkh - 2, 1);				/* SPcox (F) */
	cio_write(cio, tccp->cblksty, 1);				/* SPcox (G) */
	cio_write(cio, tccp->qmfbid, 1);				/* SPcox (H) */
	
	if (tccp->csty & J2K_CCP_CSTY_PRT) {
		for (i = 0; i < tccp->numresolutions; i++) {
			cio_write(cio, tccp->prcw[i] + (tccp->prch[i] << 4), 1);	/* SPcox (I_i) */
		}
	}
}