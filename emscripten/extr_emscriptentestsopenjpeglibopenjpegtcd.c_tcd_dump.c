#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int x0; int y0; int x1; int y1; int numresolutions; TYPE_6__* resolutions; } ;
typedef  TYPE_3__ opj_tcd_tilecomp_t ;
struct TYPE_15__ {int x0; int y0; int x1; int y1; int numcomps; TYPE_3__* comps; } ;
typedef  TYPE_4__ opj_tcd_tile_t ;
struct TYPE_16__ {TYPE_2__* tcd_image; TYPE_1__* image; } ;
typedef  TYPE_5__ opj_tcd_t ;
struct TYPE_17__ {int x0; int y0; int x1; int y1; int pw; int ph; int numbands; TYPE_9__* bands; } ;
typedef  TYPE_6__ opj_tcd_resolution_t ;
struct TYPE_18__ {int x0; int y0; int x1; int y1; int cw; int ch; } ;
typedef  TYPE_7__ opj_tcd_precinct_t ;
struct TYPE_19__ {int tw; int th; } ;
typedef  TYPE_8__ opj_tcd_image_t ;
struct TYPE_20__ {int x0; int y0; int x1; int y1; double stepsize; int numbps; TYPE_7__* precincts; } ;
typedef  TYPE_9__ opj_tcd_band_t ;
struct TYPE_13__ {TYPE_4__* tiles; } ;
struct TYPE_12__ {int x0; int x1; int y0; int y1; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void tcd_dump(FILE *fd, opj_tcd_t *tcd, opj_tcd_image_t * img) {
	int tileno, compno, resno, bandno, precno;//, cblkno;

	fprintf(fd, "image {\n");
	fprintf(fd, "  tw=%d, th=%d x0=%d x1=%d y0=%d y1=%d\n", 
		img->tw, img->th, tcd->image->x0, tcd->image->x1, tcd->image->y0, tcd->image->y1);

	for (tileno = 0; tileno < img->th * img->tw; tileno++) {
		opj_tcd_tile_t *tile = &tcd->tcd_image->tiles[tileno];
		fprintf(fd, "  tile {\n");
		fprintf(fd, "    x0=%d, y0=%d, x1=%d, y1=%d, numcomps=%d\n",
			tile->x0, tile->y0, tile->x1, tile->y1, tile->numcomps);
		for (compno = 0; compno < tile->numcomps; compno++) {
			opj_tcd_tilecomp_t *tilec = &tile->comps[compno];
			fprintf(fd, "    tilec {\n");
			fprintf(fd,
				"      x0=%d, y0=%d, x1=%d, y1=%d, numresolutions=%d\n",
				tilec->x0, tilec->y0, tilec->x1, tilec->y1, tilec->numresolutions);
			for (resno = 0; resno < tilec->numresolutions; resno++) {
				opj_tcd_resolution_t *res = &tilec->resolutions[resno];
				fprintf(fd, "\n   res {\n");
				fprintf(fd,
					"          x0=%d, y0=%d, x1=%d, y1=%d, pw=%d, ph=%d, numbands=%d\n",
					res->x0, res->y0, res->x1, res->y1, res->pw, res->ph, res->numbands);
				for (bandno = 0; bandno < res->numbands; bandno++) {
					opj_tcd_band_t *band = &res->bands[bandno];
					fprintf(fd, "        band {\n");
					fprintf(fd,
						"          x0=%d, y0=%d, x1=%d, y1=%d, stepsize=%f, numbps=%d\n",
						band->x0, band->y0, band->x1, band->y1, band->stepsize, band->numbps);
					for (precno = 0; precno < res->pw * res->ph; precno++) {
						opj_tcd_precinct_t *prec = &band->precincts[precno];
						fprintf(fd, "          prec {\n");
						fprintf(fd,
							"            x0=%d, y0=%d, x1=%d, y1=%d, cw=%d, ch=%d\n",
							prec->x0, prec->y0, prec->x1, prec->y1, prec->cw, prec->ch);
						/*
						for (cblkno = 0; cblkno < prec->cw * prec->ch; cblkno++) {
							opj_tcd_cblk_t *cblk = &prec->cblks[cblkno];
							fprintf(fd, "            cblk {\n");
							fprintf(fd,
								"              x0=%d, y0=%d, x1=%d, y1=%d\n",
								cblk->x0, cblk->y0, cblk->x1, cblk->y1);
							fprintf(fd, "            }\n");
						}
						*/
						fprintf(fd, "          }\n");
					}
					fprintf(fd, "        }\n");
				}
				fprintf(fd, "      }\n");
			}
			fprintf(fd, "    }\n");
		}
		fprintf(fd, "  }\n");
	}
	fprintf(fd, "}\n");
}