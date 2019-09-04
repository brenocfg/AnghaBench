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
struct TYPE_8__ {int POC; int numpocs; TYPE_3__* pocs; } ;
typedef  TYPE_2__ opj_tcp_t ;
struct TYPE_9__ {scalar_t__ prg; int /*<<< orphan*/  compno1; void* resno1; void* layno1; void* compno0; void* resno0; } ;
typedef  TYPE_3__ opj_poc_t ;
struct TYPE_10__ {scalar_t__ state; size_t curtileno; int /*<<< orphan*/ * cio; TYPE_2__* default_tcp; TYPE_5__* cp; TYPE_1__* image; } ;
typedef  TYPE_4__ opj_j2k_t ;
struct TYPE_11__ {TYPE_2__* tcps; } ;
typedef  TYPE_5__ opj_cp_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_7__ {int numcomps; } ;
typedef  scalar_t__ OPJ_PROG_ORDER ;

/* Variables and functions */
 scalar_t__ J2K_STATE_TPH ; 
 void* cio_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  int_min (void*,unsigned int) ; 

__attribute__((used)) static void j2k_read_poc(opj_j2k_t *j2k) {
	int len, numpchgs, i, old_poc;

	int numcomps = j2k->image->numcomps;
	
	opj_cp_t *cp = j2k->cp;
	opj_tcp_t *tcp = j2k->state == J2K_STATE_TPH ? &cp->tcps[j2k->curtileno] : j2k->default_tcp;
	opj_cio_t *cio = j2k->cio;
	
	old_poc = tcp->POC ? tcp->numpocs + 1 : 0;
	tcp->POC = 1;
	len = cio_read(cio, 2);		/* Lpoc */
	numpchgs = (len - 2) / (5 + 2 * (numcomps <= 256 ? 1 : 2));
	
	for (i = old_poc; i < numpchgs + old_poc; i++) {
		opj_poc_t *poc;
		poc = &tcp->pocs[i];
		poc->resno0 = cio_read(cio, 1);	/* RSpoc_i */
		poc->compno0 = cio_read(cio, numcomps <= 256 ? 1 : 2);	/* CSpoc_i */
		poc->layno1 = cio_read(cio, 2);    /* LYEpoc_i */
		poc->resno1 = cio_read(cio, 1);    /* REpoc_i */
		poc->compno1 = int_min(
			cio_read(cio, numcomps <= 256 ? 1 : 2), (unsigned int) numcomps);	/* CEpoc_i */
		poc->prg = (OPJ_PROG_ORDER)cio_read(cio, 1);	/* Ppoc_i */
	}
	
	tcp->numpocs = numpchgs + old_poc - 1;
}