#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* tccps; } ;
typedef  TYPE_3__ opj_tcp_t ;
struct TYPE_11__ {int numresolutions; int cblkw; int cblkh; int cblksty; int qmfbid; int csty; int* prcw; int* prch; } ;
typedef  TYPE_4__ opj_tccp_t ;
struct TYPE_12__ {size_t curtileno; TYPE_2__* cstr_info; int /*<<< orphan*/  state; int /*<<< orphan*/  cinfo; int /*<<< orphan*/ * cio; TYPE_3__* default_tcp; TYPE_6__* cp; } ;
typedef  TYPE_5__ opj_j2k_t ;
struct TYPE_13__ {int reduce; TYPE_3__* tcps; } ;
typedef  TYPE_6__ opj_cp_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_9__ {TYPE_1__* tile; } ;
struct TYPE_8__ {int* pdx; int* pdy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int J2K_CP_CSTY_PRT ; 
 int /*<<< orphan*/  J2K_STATE_ERR ; 
 int /*<<< orphan*/  J2K_STATE_TPH ; 
 int cio_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void j2k_read_cox(opj_j2k_t *j2k, int compno) {
	int i;

	opj_cp_t *cp = j2k->cp;
	opj_tcp_t *tcp = j2k->state == J2K_STATE_TPH ? &cp->tcps[j2k->curtileno] : j2k->default_tcp;
	opj_tccp_t *tccp = &tcp->tccps[compno];
	opj_cio_t *cio = j2k->cio;

	tccp->numresolutions = cio_read(cio, 1) + 1;	/* SPcox (D) */

	// If user wants to remove more resolutions than the codestream contains, return error
	if (cp->reduce >= tccp->numresolutions) {
		opj_event_msg(j2k->cinfo, EVT_ERROR, "Error decoding component %d.\nThe number of resolutions to remove is higher than the number "
					"of resolutions of this component\nModify the cp_reduce parameter.\n\n", compno);
		j2k->state |= J2K_STATE_ERR;
	}

	tccp->cblkw = cio_read(cio, 1) + 2;	/* SPcox (E) */
	tccp->cblkh = cio_read(cio, 1) + 2;	/* SPcox (F) */
	tccp->cblksty = cio_read(cio, 1);	/* SPcox (G) */
	tccp->qmfbid = cio_read(cio, 1);	/* SPcox (H) */
	if (tccp->csty & J2K_CP_CSTY_PRT) {
		for (i = 0; i < tccp->numresolutions; i++) {
			int tmp = cio_read(cio, 1);	/* SPcox (I_i) */
			tccp->prcw[i] = tmp & 0xf;
			tccp->prch[i] = tmp >> 4;
		}
	}

	/* INDEX >> */
	if(j2k->cstr_info && compno == 0) {
		for (i = 0; i < tccp->numresolutions; i++) {
			if (tccp->csty & J2K_CP_CSTY_PRT) {
				j2k->cstr_info->tile[j2k->curtileno].pdx[i] = tccp->prcw[i];
				j2k->cstr_info->tile[j2k->curtileno].pdy[i] = tccp->prch[i];
			}
			else {
				j2k->cstr_info->tile[j2k->curtileno].pdx[i] = 15;
				j2k->cstr_info->tile[j2k->curtileno].pdx[i] = 15;
			}
		}
	}
	/* << INDEX */
}