#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int numresolutions; int numbands; int ph; int pw; struct TYPE_10__* resolutions; int /*<<< orphan*/ * incltree; int /*<<< orphan*/ * imsbtree; TYPE_7__* bands; } ;
typedef  TYPE_1__ opj_tcd_tilecomp_t ;
struct TYPE_11__ {int numcomps; TYPE_1__* comps; } ;
typedef  TYPE_2__ opj_tcd_tile_t ;
struct TYPE_12__ {TYPE_6__* tcd_image; } ;
typedef  TYPE_3__ opj_tcd_t ;
typedef  TYPE_1__ opj_tcd_resolution_t ;
typedef  TYPE_1__ opj_tcd_precinct_t ;
struct TYPE_13__ {TYPE_2__* tiles; } ;
typedef  TYPE_6__ opj_tcd_image_t ;
struct TYPE_14__ {TYPE_1__* precincts; } ;
typedef  TYPE_7__ opj_tcd_band_t ;

/* Variables and functions */
 int /*<<< orphan*/  opj_free (TYPE_1__*) ; 
 int /*<<< orphan*/  tgt_destroy (int /*<<< orphan*/ *) ; 

void tcd_free_decode_tile(opj_tcd_t *tcd, int tileno) {
	int compno,resno,bandno,precno;

	opj_tcd_image_t *tcd_image = tcd->tcd_image;

	opj_tcd_tile_t *tile = &tcd_image->tiles[tileno];
	for (compno = 0; compno < tile->numcomps; compno++) {
		opj_tcd_tilecomp_t *tilec = &tile->comps[compno];
		for (resno = 0; resno < tilec->numresolutions; resno++) {
			opj_tcd_resolution_t *res = &tilec->resolutions[resno];
			for (bandno = 0; bandno < res->numbands; bandno++) {
				opj_tcd_band_t *band = &res->bands[bandno];
				for (precno = 0; precno < res->ph * res->pw; precno++) {
					opj_tcd_precinct_t *prec = &band->precincts[precno];
					if (prec->imsbtree != NULL) tgt_destroy(prec->imsbtree);
					if (prec->incltree != NULL) tgt_destroy(prec->incltree);
				}
				opj_free(band->precincts);
			}
		}
		opj_free(tilec->resolutions);
	}
	opj_free(tile->comps);
}