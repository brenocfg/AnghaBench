#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* enc; } ;
struct TYPE_13__ {int numcomps; int numresolutions; int numbands; int pw; int ph; int cw; int ch; struct TYPE_13__* comps; struct TYPE_13__* resolutions; TYPE_1__ cblks; struct TYPE_13__* passes; struct TYPE_13__* layers; struct TYPE_13__* data; int /*<<< orphan*/ * imsbtree; int /*<<< orphan*/ * incltree; TYPE_8__* bands; } ;
typedef  TYPE_3__ opj_tcd_tilecomp_t ;
typedef  TYPE_3__ opj_tcd_tile_t ;
struct TYPE_14__ {TYPE_2__* tcd_image; } ;
typedef  TYPE_5__ opj_tcd_t ;
typedef  TYPE_3__ opj_tcd_resolution_t ;
typedef  TYPE_3__ opj_tcd_precinct_t ;
struct TYPE_15__ {TYPE_3__* precincts; } ;
typedef  TYPE_8__ opj_tcd_band_t ;
struct TYPE_12__ {TYPE_3__* tiles; } ;

/* Variables and functions */
 int /*<<< orphan*/  opj_free (TYPE_3__*) ; 
 int /*<<< orphan*/  tgt_destroy (int /*<<< orphan*/ *) ; 

void tcd_free_encode(opj_tcd_t *tcd) {
	int tileno, compno, resno, bandno, precno, cblkno;

	for (tileno = 0; tileno < 1; tileno++) {
		opj_tcd_tile_t *tile = tcd->tcd_image->tiles;

		for (compno = 0; compno < tile->numcomps; compno++) {
			opj_tcd_tilecomp_t *tilec = &tile->comps[compno];

			for (resno = 0; resno < tilec->numresolutions; resno++) {
				opj_tcd_resolution_t *res = &tilec->resolutions[resno];

				for (bandno = 0; bandno < res->numbands; bandno++) {
					opj_tcd_band_t *band = &res->bands[bandno];

					for (precno = 0; precno < res->pw * res->ph; precno++) {
						opj_tcd_precinct_t *prc = &band->precincts[precno];

						if (prc->incltree != NULL) {
							tgt_destroy(prc->incltree);
							prc->incltree = NULL;
						}
						if (prc->imsbtree != NULL) {
							tgt_destroy(prc->imsbtree);	
							prc->imsbtree = NULL;
						}
						for (cblkno = 0; cblkno < prc->cw * prc->ch; cblkno++) {
							opj_free(prc->cblks.enc[cblkno].data - 2);
							opj_free(prc->cblks.enc[cblkno].layers);
							opj_free(prc->cblks.enc[cblkno].passes);
						}
						opj_free(prc->cblks.enc);
					} /* for (precno */
					opj_free(band->precincts);
					band->precincts = NULL;
				} /* for (bandno */
			} /* for (resno */
			opj_free(tilec->resolutions);
			tilec->resolutions = NULL;
		} /* for (compno */
		opj_free(tile->comps);
		tile->comps = NULL;
	} /* for (tileno */
	opj_free(tcd->tcd_image->tiles);
	tcd->tcd_image->tiles = NULL;
}