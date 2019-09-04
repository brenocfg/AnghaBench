#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  mct; TYPE_9__* tccps; } ;
typedef  TYPE_2__ opj_tcp_t ;
struct TYPE_21__ {int x1; int x0; int numresolutions; int* data; TYPE_5__* resolutions; } ;
typedef  TYPE_3__ opj_tcd_tilecomp_t ;
struct TYPE_22__ {int numcomps; TYPE_3__* comps; scalar_t__ distotile; } ;
typedef  TYPE_4__ opj_tcd_tile_t ;
struct TYPE_23__ {int numbands; int pw; int ph; scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; TYPE_8__* bands; } ;
typedef  TYPE_5__ opj_tcd_resolution_t ;
struct TYPE_19__ {TYPE_7__* enc; } ;
struct TYPE_24__ {int cw; int ch; TYPE_1__ cblks; } ;
typedef  TYPE_6__ opj_tcd_precinct_t ;
struct TYPE_25__ {int x0; int y0; int x1; int y1; } ;
typedef  TYPE_7__ opj_tcd_cblk_enc_t ;
struct TYPE_26__ {int x0; int y0; int bandno; int stepsize; TYPE_6__* precincts; } ;
typedef  TYPE_8__ opj_tcd_band_t ;
struct TYPE_27__ {int qmfbid; int /*<<< orphan*/  cblksty; } ;
typedef  TYPE_9__ opj_tccp_t ;
struct TYPE_18__ {int* data; int w; int h; } ;
typedef  TYPE_10__ opj_t1_t ;

/* Variables and functions */
 int T1_NMSEDEC_FRACBITS ; 
 int /*<<< orphan*/  allocate_buffers (TYPE_10__*,int,int) ; 
 int fix_mul (int,int) ; 
 scalar_t__ floor (int) ; 
 int /*<<< orphan*/  t1_encode_cblk (TYPE_10__*,TYPE_7__*,int,int,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_4__*) ; 

void t1_encode_cblks(
		opj_t1_t *t1,
		opj_tcd_tile_t *tile,
		opj_tcp_t *tcp)
{
	int compno, resno, bandno, precno, cblkno;

	tile->distotile = 0;		/* fixed_quality */

	for (compno = 0; compno < tile->numcomps; ++compno) {
		opj_tcd_tilecomp_t* tilec = &tile->comps[compno];
		opj_tccp_t* tccp = &tcp->tccps[compno];
		int tile_w = tilec->x1 - tilec->x0;

		for (resno = 0; resno < tilec->numresolutions; ++resno) {
			opj_tcd_resolution_t *res = &tilec->resolutions[resno];

			for (bandno = 0; bandno < res->numbands; ++bandno) {
				opj_tcd_band_t* restrict band = &res->bands[bandno];

				for (precno = 0; precno < res->pw * res->ph; ++precno) {
					opj_tcd_precinct_t *prc = &band->precincts[precno];

					for (cblkno = 0; cblkno < prc->cw * prc->ch; ++cblkno) {
						opj_tcd_cblk_enc_t* cblk = &prc->cblks.enc[cblkno];
						int* restrict datap;
						int* restrict tiledp;
						int cblk_w;
						int cblk_h;
						int i, j;

						int x = cblk->x0 - band->x0;
						int y = cblk->y0 - band->y0;
						if (band->bandno & 1) {
							opj_tcd_resolution_t *pres = &tilec->resolutions[resno - 1];
							x += pres->x1 - pres->x0;
						}
						if (band->bandno & 2) {
							opj_tcd_resolution_t *pres = &tilec->resolutions[resno - 1];
							y += pres->y1 - pres->y0;
						}

						if(!allocate_buffers(
									t1,
									cblk->x1 - cblk->x0,
									cblk->y1 - cblk->y0))
						{
							return;
						}

						datap=t1->data;
						cblk_w = t1->w;
						cblk_h = t1->h;

						tiledp=&tilec->data[(y * tile_w) + x];
						if (tccp->qmfbid == 1) {
							for (j = 0; j < cblk_h; ++j) {
								for (i = 0; i < cblk_w; ++i) {
									int tmp = tiledp[(j * tile_w) + i];
									datap[(j * cblk_w) + i] = tmp << T1_NMSEDEC_FRACBITS;
								}
							}
						} else {		/* if (tccp->qmfbid == 0) */
							for (j = 0; j < cblk_h; ++j) {
								for (i = 0; i < cblk_w; ++i) {
									int tmp = tiledp[(j * tile_w) + i];
									datap[(j * cblk_w) + i] =
										fix_mul(
										tmp,
										8192 * 8192 / ((int) floor(band->stepsize * 8192))) >> (11 - T1_NMSEDEC_FRACBITS);
								}
							}
						}

						t1_encode_cblk(
								t1,
								cblk,
								band->bandno,
								compno,
								tilec->numresolutions - 1 - resno,
								tccp->qmfbid,
								band->stepsize,
								tccp->cblksty,
								tile->numcomps,
								tcp->mct,
								tile);

					} /* cblkno */
				} /* precno */
			} /* bandno */
		} /* resno  */
	} /* compno  */
}