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
struct TYPE_9__ {int numpocs; int numlayers; TYPE_4__* pocs; TYPE_3__* tccps; } ;
typedef  TYPE_2__ opj_tcp_t ;
struct TYPE_10__ {int numresolutions; } ;
typedef  TYPE_3__ opj_tccp_t ;
struct TYPE_11__ {int resno0; int compno0; int layno1; int resno1; int compno1; int prg; } ;
typedef  TYPE_4__ opj_poc_t ;
struct TYPE_12__ {size_t curtileno; int /*<<< orphan*/ * cio; TYPE_6__* cp; TYPE_1__* image; } ;
typedef  TYPE_5__ opj_j2k_t ;
struct TYPE_13__ {TYPE_2__* tcps; } ;
typedef  TYPE_6__ opj_cp_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_8__ {int numcomps; } ;

/* Variables and functions */
 int J2K_MS_POC ; 
 int /*<<< orphan*/  cio_write (int /*<<< orphan*/ *,int,int) ; 
 void* int_min (int,int) ; 

__attribute__((used)) static void j2k_write_poc(opj_j2k_t *j2k) {
	int len, numpchgs, i;

	int numcomps = j2k->image->numcomps;
	
	opj_cp_t *cp = j2k->cp;
	opj_tcp_t *tcp = &cp->tcps[j2k->curtileno];
	opj_tccp_t *tccp = &tcp->tccps[0];
	opj_cio_t *cio = j2k->cio;

	numpchgs = 1 + tcp->numpocs;
	cio_write(cio, J2K_MS_POC, 2);	/* POC  */
	len = 2 + (5 + 2 * (numcomps <= 256 ? 1 : 2)) * numpchgs;
	cio_write(cio, len, 2);		/* Lpoc */
	for (i = 0; i < numpchgs; i++) {
		opj_poc_t *poc = &tcp->pocs[i];
		cio_write(cio, poc->resno0, 1);	/* RSpoc_i */
		cio_write(cio, poc->compno0, (numcomps <= 256 ? 1 : 2));	/* CSpoc_i */
		cio_write(cio, poc->layno1, 2);	/* LYEpoc_i */
		poc->layno1 = int_min(poc->layno1, tcp->numlayers);
		cio_write(cio, poc->resno1, 1);	/* REpoc_i */
		poc->resno1 = int_min(poc->resno1, tccp->numresolutions);
		cio_write(cio, poc->compno1, (numcomps <= 256 ? 1 : 2));	/* CEpoc_i */
		poc->compno1 = int_min(poc->compno1, numcomps);
		cio_write(cio, poc->prg, 1);	/* Ppoc_i */
	}
}