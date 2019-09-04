#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int csty; int prg; int numlayers; int mct; double* rates; TYPE_3__* tccps; } ;
typedef  TYPE_2__ opj_tcp_t ;
struct TYPE_10__ {int csty; int numresolutions; int cblkw; int cblkh; int cblksty; int qmfbid; int qntsty; int numgbits; int roishift; int* prcw; int* prch; TYPE_1__* stepsizes; } ;
typedef  TYPE_3__ opj_tccp_t ;
struct TYPE_11__ {int numcomps; } ;
typedef  TYPE_4__ opj_image_t ;
struct TYPE_12__ {int tx0; int ty0; int tdx; int tdy; int tw; int th; TYPE_2__* tcps; } ;
typedef  TYPE_5__ opj_cp_t ;
struct TYPE_8__ {int mant; int expn; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int J2K_CCP_CSTY_PRT ; 
 int J2K_CCP_QNTSTY_SIQNT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void j2k_dump_cp(FILE *fd, opj_image_t * img, opj_cp_t * cp) {
	int tileno, compno, layno, bandno, resno, numbands;
	fprintf(fd, "coding parameters {\n");
	fprintf(fd, "  tx0=%d, ty0=%d\n", cp->tx0, cp->ty0);
	fprintf(fd, "  tdx=%d, tdy=%d\n", cp->tdx, cp->tdy);
	fprintf(fd, "  tw=%d, th=%d\n", cp->tw, cp->th);
	for (tileno = 0; tileno < cp->tw * cp->th; tileno++) {
		opj_tcp_t *tcp = &cp->tcps[tileno];
		fprintf(fd, "  tile %d {\n", tileno);
		fprintf(fd, "    csty=%x\n", tcp->csty);
		fprintf(fd, "    prg=%d\n", tcp->prg);
		fprintf(fd, "    numlayers=%d\n", tcp->numlayers);
		fprintf(fd, "    mct=%d\n", tcp->mct);
		fprintf(fd, "    rates=");
		for (layno = 0; layno < tcp->numlayers; layno++) {
			fprintf(fd, "%.1f ", tcp->rates[layno]);
		}
		fprintf(fd, "\n");
		for (compno = 0; compno < img->numcomps; compno++) {
			opj_tccp_t *tccp = &tcp->tccps[compno];
			fprintf(fd, "    comp %d {\n", compno);
			fprintf(fd, "      csty=%x\n", tccp->csty);
			fprintf(fd, "      numresolutions=%d\n", tccp->numresolutions);
			fprintf(fd, "      cblkw=%d\n", tccp->cblkw);
			fprintf(fd, "      cblkh=%d\n", tccp->cblkh);
			fprintf(fd, "      cblksty=%x\n", tccp->cblksty);
			fprintf(fd, "      qmfbid=%d\n", tccp->qmfbid);
			fprintf(fd, "      qntsty=%d\n", tccp->qntsty);
			fprintf(fd, "      numgbits=%d\n", tccp->numgbits);
			fprintf(fd, "      roishift=%d\n", tccp->roishift);
			fprintf(fd, "      stepsizes=");
			numbands = tccp->qntsty == J2K_CCP_QNTSTY_SIQNT ? 1 : tccp->numresolutions * 3 - 2;
			for (bandno = 0; bandno < numbands; bandno++) {
				fprintf(fd, "(%d,%d) ", tccp->stepsizes[bandno].mant,
					tccp->stepsizes[bandno].expn);
			}
			fprintf(fd, "\n");
			
			if (tccp->csty & J2K_CCP_CSTY_PRT) {
				fprintf(fd, "      prcw=");
				for (resno = 0; resno < tccp->numresolutions; resno++) {
					fprintf(fd, "%d ", tccp->prcw[resno]);
				}
				fprintf(fd, "\n");
				fprintf(fd, "      prch=");
				for (resno = 0; resno < tccp->numresolutions; resno++) {
					fprintf(fd, "%d ", tccp->prch[resno]);
				}
				fprintf(fd, "\n");
			}
			fprintf(fd, "    }\n");
		}
		fprintf(fd, "  }\n");
	}
	fprintf(fd, "}\n");
}