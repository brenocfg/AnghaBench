#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {int numlayers; } ;
typedef  TYPE_5__ opj_tcp_t ;
struct TYPE_26__ {int numresolutions; TYPE_9__* resolutions; } ;
typedef  TYPE_6__ opj_tcd_tilecomp_t ;
struct TYPE_27__ {int numcomps; TYPE_6__* comps; } ;
typedef  TYPE_7__ opj_tcd_tile_t ;
struct TYPE_28__ {TYPE_3__* image; TYPE_5__* tcp; TYPE_7__* tcd_tile; TYPE_14__* cp; } ;
typedef  TYPE_8__ opj_tcd_t ;
struct TYPE_29__ {int numbands; int pw; int ph; TYPE_13__* bands; } ;
typedef  TYPE_9__ opj_tcd_resolution_t ;
struct TYPE_21__ {TYPE_12__* enc; } ;
struct TYPE_16__ {int cw; int ch; TYPE_1__ cblks; } ;
typedef  TYPE_10__ opj_tcd_precinct_t ;
struct TYPE_17__ {int numpasses; scalar_t__ data; scalar_t__ len; } ;
typedef  TYPE_11__ opj_tcd_layer_t ;
struct TYPE_18__ {int numbps; int numpassesinlayers; TYPE_4__* passes; scalar_t__ data; TYPE_11__* layers; } ;
typedef  TYPE_12__ opj_tcd_cblk_enc_t ;
struct TYPE_19__ {TYPE_10__* precincts; } ;
typedef  TYPE_13__ opj_tcd_band_t ;
struct TYPE_20__ {float* matrice; } ;
typedef  TYPE_14__ opj_cp_t ;
struct TYPE_24__ {scalar_t__ rate; } ;
struct TYPE_23__ {TYPE_2__* comps; } ;
struct TYPE_22__ {double prec; } ;

/* Variables and functions */

void tcd_makelayer_fixed(opj_tcd_t *tcd, int layno, int final) {
	int compno, resno, bandno, precno, cblkno;
	int value;			/*, matrice[tcd_tcp->numlayers][tcd_tile->comps[0].numresolutions][3]; */
	int matrice[10][10][3];
	int i, j, k;

	opj_cp_t *cp = tcd->cp;
	opj_tcd_tile_t *tcd_tile = tcd->tcd_tile;
	opj_tcp_t *tcd_tcp = tcd->tcp;

	/*matrice=(int*)opj_malloc(tcd_tcp->numlayers*tcd_tile->comps[0].numresolutions*3*sizeof(int)); */
	
	for (compno = 0; compno < tcd_tile->numcomps; compno++) {
		opj_tcd_tilecomp_t *tilec = &tcd_tile->comps[compno];
		for (i = 0; i < tcd_tcp->numlayers; i++) {
			for (j = 0; j < tilec->numresolutions; j++) {
				for (k = 0; k < 3; k++) {
					matrice[i][j][k] =
						(int) (cp->matrice[i * tilec->numresolutions * 3 + j * 3 + k] 
						* (float) (tcd->image->comps[compno].prec / 16.0));
				}
			}
		}
        
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
						int imsb = tcd->image->comps[compno].prec - cblk->numbps;	/* number of bit-plan equal to zero */
						/* Correction of the matrix of coefficient to include the IMSB information */
						if (layno == 0) {
							value = matrice[layno][resno][bandno];
							if (imsb >= value) {
								value = 0;
							} else {
								value -= imsb;
							}
						} else {
							value =	matrice[layno][resno][bandno] -	matrice[layno - 1][resno][bandno];
							if (imsb >= matrice[layno - 1][resno][bandno]) {
								value -= (imsb - matrice[layno - 1][resno][bandno]);
								if (value < 0) {
									value = 0;
								}
							}
						}
						
						if (layno == 0) {
							cblk->numpassesinlayers = 0;
						}
						
						n = cblk->numpassesinlayers;
						if (cblk->numpassesinlayers == 0) {
							if (value != 0) {
								n = 3 * value - 2 + cblk->numpassesinlayers;
							} else {
								n = cblk->numpassesinlayers;
							}
						} else {
							n = 3 * value + cblk->numpassesinlayers;
						}
						
						layer->numpasses = n - cblk->numpassesinlayers;
						
						if (!layer->numpasses)
							continue;
						
						if (cblk->numpassesinlayers == 0) {
							layer->len = cblk->passes[n - 1].rate;
							layer->data = cblk->data;
						} else {
							layer->len = cblk->passes[n - 1].rate - cblk->passes[cblk->numpassesinlayers - 1].rate;
							layer->data = cblk->data + cblk->passes[cblk->numpassesinlayers - 1].rate;
						}
						if (final)
							cblk->numpassesinlayers = n;
					}
				}
			}
		}
	}
}