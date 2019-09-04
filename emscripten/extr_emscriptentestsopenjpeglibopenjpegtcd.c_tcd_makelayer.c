#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {int numresolutions; TYPE_5__* resolutions; } ;
typedef  TYPE_2__ opj_tcd_tilecomp_t ;
struct TYPE_15__ {double* distolayer; int numcomps; TYPE_2__* comps; } ;
typedef  TYPE_3__ opj_tcd_tile_t ;
struct TYPE_16__ {TYPE_3__* tcd_tile; } ;
typedef  TYPE_4__ opj_tcd_t ;
struct TYPE_17__ {int numbands; int pw; int ph; TYPE_10__* bands; } ;
typedef  TYPE_5__ opj_tcd_resolution_t ;
struct TYPE_13__ {TYPE_9__* enc; } ;
struct TYPE_18__ {int cw; int ch; TYPE_1__ cblks; } ;
typedef  TYPE_6__ opj_tcd_precinct_t ;
struct TYPE_19__ {int rate; double distortiondec; } ;
typedef  TYPE_7__ opj_tcd_pass_t ;
struct TYPE_20__ {int numpasses; double disto; int len; int data; } ;
typedef  TYPE_8__ opj_tcd_layer_t ;
struct TYPE_21__ {int numpassesinlayers; int totalpasses; int data; TYPE_7__* passes; TYPE_8__* layers; } ;
typedef  TYPE_9__ opj_tcd_cblk_enc_t ;
struct TYPE_12__ {TYPE_6__* precincts; } ;
typedef  TYPE_10__ opj_tcd_band_t ;

/* Variables and functions */

void tcd_makelayer(opj_tcd_t *tcd, int layno, double thresh, int final) {
	int compno, resno, bandno, precno, cblkno, passno;
	
	opj_tcd_tile_t *tcd_tile = tcd->tcd_tile;

	tcd_tile->distolayer[layno] = 0;	/* fixed_quality */
	
	for (compno = 0; compno < tcd_tile->numcomps; compno++) {
		opj_tcd_tilecomp_t *tilec = &tcd_tile->comps[compno];
		for (resno = 0; resno < tilec->numresolutions; resno++) {
			opj_tcd_resolution_t *res = &tilec->resolutions[resno];
			for (bandno = 0; bandno < res->numbands; bandno++) {
				opj_tcd_band_t *band = &res->bands[bandno];
				for (precno = 0; precno < res->pw * res->ph; precno++) {
					opj_tcd_precinct_t *prc = &band->precincts[precno];
					for (cblkno = 0; cblkno < prc->cw * prc->ch; cblkno++) {
						opj_tcd_cblk_enc_t *cblk = &prc->cblks.enc[cblkno];
						opj_tcd_layer_t *layer = &cblk->layers[layno];
						
						int n;
						if (layno == 0) {
							cblk->numpassesinlayers = 0;
						}
						n = cblk->numpassesinlayers;
						for (passno = cblk->numpassesinlayers; passno < cblk->totalpasses; passno++) {
							int dr;
							double dd;
							opj_tcd_pass_t *pass = &cblk->passes[passno];
							if (n == 0) {
								dr = pass->rate;
								dd = pass->distortiondec;
							} else {
								dr = pass->rate - cblk->passes[n - 1].rate;
								dd = pass->distortiondec - cblk->passes[n - 1].distortiondec;
							}
							if (!dr) {
								if (dd != 0)
									n = passno + 1;
								continue;
							}
							if (dd / dr >= thresh)
								n = passno + 1;
						}
						layer->numpasses = n - cblk->numpassesinlayers;
						
						if (!layer->numpasses) {
							layer->disto = 0;
							continue;
						}
						if (cblk->numpassesinlayers == 0) {
							layer->len = cblk->passes[n - 1].rate;
							layer->data = cblk->data;
							layer->disto = cblk->passes[n - 1].distortiondec;
						} else {
							layer->len = cblk->passes[n - 1].rate -	cblk->passes[cblk->numpassesinlayers - 1].rate;
							layer->data = cblk->data + cblk->passes[cblk->numpassesinlayers - 1].rate;
							layer->disto = cblk->passes[n - 1].distortiondec - cblk->passes[cblk->numpassesinlayers - 1].distortiondec;
						}
						
						tcd_tile->distolayer[layno] += layer->disto;	/* fixed_quality */
						
						if (final)
							cblk->numpassesinlayers = n;
					}
				}
			}
		}
	}
}