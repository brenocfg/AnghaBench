#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {void* x0; void* y0; void* x1; void* y1; } ;
typedef  TYPE_3__ opj_tcd_tilecomp_t ;
struct TYPE_14__ {int numcomps; void* y1; void* x1; void* y0; void* x0; TYPE_3__* comps; } ;
typedef  TYPE_4__ opj_tcd_tile_t ;
struct TYPE_15__ {TYPE_1__* tcd_image; TYPE_6__* image; } ;
typedef  TYPE_5__ opj_tcd_t ;
struct TYPE_16__ {int numcomps; unsigned int x0; unsigned int y0; unsigned int x1; unsigned int y1; TYPE_2__* comps; } ;
typedef  TYPE_6__ opj_image_t ;
struct TYPE_17__ {int tw; int th; int tileno_size; int* tileno; unsigned int tx0; int tdx; unsigned int ty0; int tdy; } ;
typedef  TYPE_7__ opj_cp_t ;
struct TYPE_12__ {unsigned int w; unsigned int h; unsigned int x0; unsigned int y0; int /*<<< orphan*/  factor; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;
struct TYPE_11__ {int tw; int th; TYPE_4__* tiles; } ;

/* Variables and functions */
 void* int_ceildiv (void*,int /*<<< orphan*/ ) ; 
 unsigned int int_ceildivpow2 (unsigned int,int /*<<< orphan*/ ) ; 
 void* int_max (unsigned int,unsigned int) ; 
 void* int_min (unsigned int,unsigned int) ; 
 scalar_t__ opj_calloc (int,int) ; 
 scalar_t__ opj_malloc (int) ; 

void tcd_malloc_decode(opj_tcd_t *tcd, opj_image_t * image, opj_cp_t * cp) {
	int i, j, tileno, p, q;
	unsigned int x0 = 0, y0 = 0, x1 = 0, y1 = 0, w, h;

	tcd->image = image;
	tcd->tcd_image->tw = cp->tw;
	tcd->tcd_image->th = cp->th;
	tcd->tcd_image->tiles = (opj_tcd_tile_t *) opj_malloc(cp->tw * cp->th * sizeof(opj_tcd_tile_t));

	/* 
	Allocate place to store the decoded data = final image
	Place limited by the tile really present in the codestream 
	*/

	for (j = 0; j < cp->tileno_size; j++) {
		opj_tcd_tile_t *tile;
		
		tileno = cp->tileno[j];		
		tile = &(tcd->tcd_image->tiles[cp->tileno[tileno]]);		
		tile->numcomps = image->numcomps;
		tile->comps = (opj_tcd_tilecomp_t*) opj_calloc(image->numcomps, sizeof(opj_tcd_tilecomp_t));
	}

	for (i = 0; i < image->numcomps; i++) {
		for (j = 0; j < cp->tileno_size; j++) {
			opj_tcd_tile_t *tile;
			opj_tcd_tilecomp_t *tilec;
			
			/* cfr p59 ISO/IEC FDIS15444-1 : 2000 (18 august 2000) */
			
			tileno = cp->tileno[j];
			
			tile = &(tcd->tcd_image->tiles[cp->tileno[tileno]]);
			tilec = &tile->comps[i];
			
			p = tileno % cp->tw;	/* si numerotation matricielle .. */
			q = tileno / cp->tw;	/* .. coordonnees de la tile (q,p) q pour ligne et p pour colonne */
			
			/* 4 borders of the tile rescale on the image if necessary */
			tile->x0 = int_max(cp->tx0 + p * cp->tdx, image->x0);
			tile->y0 = int_max(cp->ty0 + q * cp->tdy, image->y0);
			tile->x1 = int_min(cp->tx0 + (p + 1) * cp->tdx, image->x1);
			tile->y1 = int_min(cp->ty0 + (q + 1) * cp->tdy, image->y1);

			tilec->x0 = int_ceildiv(tile->x0, image->comps[i].dx);
			tilec->y0 = int_ceildiv(tile->y0, image->comps[i].dy);
			tilec->x1 = int_ceildiv(tile->x1, image->comps[i].dx);
			tilec->y1 = int_ceildiv(tile->y1, image->comps[i].dy);

			x0 = j == 0 ? tilec->x0 : int_min(x0, (unsigned int) tilec->x0);
			y0 = j == 0 ? tilec->y0 : int_min(y0,	(unsigned int) tilec->x0);
			x1 = j == 0 ? tilec->x1 : int_max(x1,	(unsigned int) tilec->x1);
			y1 = j == 0 ? tilec->y1 : int_max(y1,	(unsigned int) tilec->y1);
		}

		w = int_ceildivpow2(x1 - x0, image->comps[i].factor);
		h = int_ceildivpow2(y1 - y0, image->comps[i].factor);

		image->comps[i].w = w;
		image->comps[i].h = h;
		image->comps[i].x0 = x0;
		image->comps[i].y0 = y0;
	}
}