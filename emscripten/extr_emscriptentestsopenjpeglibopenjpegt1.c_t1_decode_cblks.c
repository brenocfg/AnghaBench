#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int x1; int x0; int numresolutions; int* data; TYPE_3__* resolutions; } ;
typedef  TYPE_2__ opj_tcd_tilecomp_t ;
struct TYPE_17__ {int numbands; int pw; int ph; scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; TYPE_6__* bands; } ;
typedef  TYPE_3__ opj_tcd_resolution_t ;
struct TYPE_15__ {TYPE_5__* dec; } ;
struct TYPE_18__ {int cw; int ch; TYPE_1__ cblks; } ;
typedef  TYPE_4__ opj_tcd_precinct_t ;
struct TYPE_19__ {int x0; int y0; struct TYPE_19__* segs; struct TYPE_19__* data; } ;
typedef  TYPE_5__ opj_tcd_cblk_dec_t ;
struct TYPE_20__ {int bandno; int x0; int y0; int stepsize; TYPE_4__* precincts; } ;
typedef  TYPE_6__ opj_tcd_band_t ;
struct TYPE_21__ {int roishift; int qmfbid; int /*<<< orphan*/  cblksty; } ;
typedef  TYPE_7__ opj_tccp_t ;
struct TYPE_22__ {int* data; int w; int h; } ;
typedef  TYPE_8__ opj_t1_t ;

/* Variables and functions */
 int abs (int) ; 
 int /*<<< orphan*/  opj_free (TYPE_5__*) ; 
 int /*<<< orphan*/  t1_decode_cblk (TYPE_8__*,TYPE_5__*,int,int,int /*<<< orphan*/ ) ; 

void t1_decode_cblks(
		opj_t1_t* t1,
		opj_tcd_tilecomp_t* tilec,
		opj_tccp_t* tccp)
{
	int resno, bandno, precno, cblkno;

	int tile_w = tilec->x1 - tilec->x0;

	for (resno = 0; resno < tilec->numresolutions; ++resno) {
		opj_tcd_resolution_t* res = &tilec->resolutions[resno];

		for (bandno = 0; bandno < res->numbands; ++bandno) {
			opj_tcd_band_t* restrict band = &res->bands[bandno];

			for (precno = 0; precno < res->pw * res->ph; ++precno) {
				opj_tcd_precinct_t* precinct = &band->precincts[precno];

				for (cblkno = 0; cblkno < precinct->cw * precinct->ch; ++cblkno) {
					opj_tcd_cblk_dec_t* cblk = &precinct->cblks.dec[cblkno];
					int* restrict datap;
					int cblk_w, cblk_h;
					int x, y;
					int i, j;

					t1_decode_cblk(
							t1,
							cblk,
							band->bandno,
							tccp->roishift,
							tccp->cblksty);

					x = cblk->x0 - band->x0;
					y = cblk->y0 - band->y0;
					if (band->bandno & 1) {
						opj_tcd_resolution_t* pres = &tilec->resolutions[resno - 1];
						x += pres->x1 - pres->x0;
					}
					if (band->bandno & 2) {
						opj_tcd_resolution_t* pres = &tilec->resolutions[resno - 1];
						y += pres->y1 - pres->y0;
					}

					datap=t1->data;
					cblk_w = t1->w;
					cblk_h = t1->h;

					if (tccp->roishift) {
						int thresh = 1 << tccp->roishift;
						for (j = 0; j < cblk_h; ++j) {
							for (i = 0; i < cblk_w; ++i) {
								int val = datap[(j * cblk_w) + i];
								int mag = abs(val);
								if (mag >= thresh) {
									mag >>= tccp->roishift;
									datap[(j * cblk_w) + i] = val < 0 ? -mag : mag;
								}
							}
						}
					}

					if (tccp->qmfbid == 1) {
						int* restrict tiledp = &tilec->data[(y * tile_w) + x];
						for (j = 0; j < cblk_h; ++j) {
							for (i = 0; i < cblk_w; ++i) {
								int tmp = datap[(j * cblk_w) + i];
								((int*)tiledp)[(j * tile_w) + i] = tmp / 2;
							}
						}
					} else {		/* if (tccp->qmfbid == 0) */
						float* restrict tiledp = (float*) &tilec->data[(y * tile_w) + x];
						for (j = 0; j < cblk_h; ++j) {
							float* restrict tiledp2 = tiledp;
							for (i = 0; i < cblk_w; ++i) {
								float tmp = *datap * band->stepsize;
								*tiledp2 = tmp;
								datap++;
								tiledp2++;
							}
							tiledp += tile_w;
						}
					}
					opj_free(cblk->data);
					opj_free(cblk->segs);
				} /* cblkno */
				opj_free(precinct->cblks.dec);
			} /* precno */
		} /* bandno */
	} /* resno */
}