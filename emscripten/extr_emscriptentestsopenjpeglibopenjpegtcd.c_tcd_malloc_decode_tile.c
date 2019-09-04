#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_15__ ;
typedef  struct TYPE_23__   TYPE_14__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_28__ {TYPE_12__* tccps; } ;
typedef  TYPE_4__ opj_tcp_t ;
struct TYPE_29__ {int x0; int y0; int x1; int y1; int numresolutions; TYPE_8__* resolutions; } ;
typedef  TYPE_5__ opj_tcd_tilecomp_t ;
struct TYPE_30__ {int numcomps; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; int /*<<< orphan*/  y0; int /*<<< orphan*/  x0; TYPE_5__* comps; } ;
typedef  TYPE_6__ opj_tcd_tile_t ;
struct TYPE_31__ {TYPE_1__* tcd_image; TYPE_15__* cp; } ;
typedef  TYPE_7__ opj_tcd_t ;
struct TYPE_32__ {int x0; int y0; int x1; int y1; int numbands; int pw; int ph; TYPE_11__* bands; } ;
typedef  TYPE_8__ opj_tcd_resolution_t ;
struct TYPE_27__ {TYPE_10__* dec; } ;
struct TYPE_33__ {int x0; int y0; int x1; int y1; int cw; int ch; TYPE_3__ cblks; void* imsbtree; void* incltree; } ;
typedef  TYPE_9__ opj_tcd_precinct_t ;
struct TYPE_19__ {scalar_t__ numbps; scalar_t__ numsegs; void* y1; void* x1; void* y0; void* x0; int /*<<< orphan*/ * segs; int /*<<< orphan*/ * data; } ;
typedef  TYPE_10__ opj_tcd_cblk_dec_t ;
struct TYPE_20__ {int bandno; int x0; int y0; int x1; int y1; float stepsize; int numbps; TYPE_9__* precincts; } ;
typedef  TYPE_11__ opj_tcd_band_t ;
struct TYPE_21__ {int numresolutions; int csty; int* prcw; int* prch; int cblkw; int cblkh; scalar_t__ qmfbid; int numgbits; TYPE_13__* stepsizes; } ;
typedef  TYPE_12__ opj_tccp_t ;
struct TYPE_22__ {double mant; int expn; } ;
typedef  TYPE_13__ opj_stepsize_t ;
struct TYPE_23__ {TYPE_2__* comps; } ;
typedef  TYPE_14__ opj_image_t ;
struct TYPE_24__ {size_t* tileno; TYPE_4__* tcps; } ;
typedef  TYPE_15__ opj_cp_t ;
typedef  int /*<<< orphan*/  opj_codestream_info_t ;
struct TYPE_26__ {int prec; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;
struct TYPE_25__ {TYPE_6__* tiles; } ;

/* Variables and functions */
 int J2K_CCP_CSTY_PRT ; 
 int dwt_getgain (int) ; 
 int dwt_getgain_real (int) ; 
 void* int_ceildiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int int_ceildivpow2 (int,int) ; 
 int int_floordivpow2 (int,int) ; 
 void* int_max (int,int) ; 
 void* int_min (int,int) ; 
 scalar_t__ opj_malloc (int) ; 
 double pow (double,int) ; 
 void* tgt_create (int,int) ; 

void tcd_malloc_decode_tile(opj_tcd_t *tcd, opj_image_t * image, opj_cp_t * cp, int tileno, opj_codestream_info_t *cstr_info) {
	int compno, resno, bandno, precno, cblkno;
	opj_tcp_t *tcp;
	opj_tcd_tile_t *tile;

	tcd->cp = cp;
	
	tcp = &(cp->tcps[cp->tileno[tileno]]);
	tile = &(tcd->tcd_image->tiles[cp->tileno[tileno]]);
	
	tileno = cp->tileno[tileno];
	
	for (compno = 0; compno < tile->numcomps; compno++) {
		opj_tccp_t *tccp = &tcp->tccps[compno];
		opj_tcd_tilecomp_t *tilec = &tile->comps[compno];
		
		/* border of each tile component (global) */
		tilec->x0 = int_ceildiv(tile->x0, image->comps[compno].dx);
		tilec->y0 = int_ceildiv(tile->y0, image->comps[compno].dy);
		tilec->x1 = int_ceildiv(tile->x1, image->comps[compno].dx);
		tilec->y1 = int_ceildiv(tile->y1, image->comps[compno].dy);

		tilec->numresolutions = tccp->numresolutions;
		tilec->resolutions = (opj_tcd_resolution_t *) opj_malloc(tilec->numresolutions * sizeof(opj_tcd_resolution_t));
		
		for (resno = 0; resno < tilec->numresolutions; resno++) {
			int pdx, pdy;
			int levelno = tilec->numresolutions - 1 - resno;
			int tlprcxstart, tlprcystart, brprcxend, brprcyend;
			int tlcbgxstart, tlcbgystart, brcbgxend, brcbgyend;
			int cbgwidthexpn, cbgheightexpn;
			int cblkwidthexpn, cblkheightexpn;
			
			opj_tcd_resolution_t *res = &tilec->resolutions[resno];
			
			/* border for each resolution level (global) */
			res->x0 = int_ceildivpow2(tilec->x0, levelno);
			res->y0 = int_ceildivpow2(tilec->y0, levelno);
			res->x1 = int_ceildivpow2(tilec->x1, levelno);
			res->y1 = int_ceildivpow2(tilec->y1, levelno);
			res->numbands = resno == 0 ? 1 : 3;
			
			/* p. 35, table A-23, ISO/IEC FDIS154444-1 : 2000 (18 august 2000) */
			if (tccp->csty & J2K_CCP_CSTY_PRT) {
				pdx = tccp->prcw[resno];
				pdy = tccp->prch[resno];
			} else {
				pdx = 15;
				pdy = 15;
			}			
			
			/* p. 64, B.6, ISO/IEC FDIS15444-1 : 2000 (18 august 2000)  */
			tlprcxstart = int_floordivpow2(res->x0, pdx) << pdx;
			tlprcystart = int_floordivpow2(res->y0, pdy) << pdy;
			brprcxend = int_ceildivpow2(res->x1, pdx) << pdx;
			brprcyend = int_ceildivpow2(res->y1, pdy) << pdy;
			
			res->pw = (res->x0 == res->x1) ? 0 : ((brprcxend - tlprcxstart) >> pdx);
			res->ph = (res->y0 == res->y1) ? 0 : ((brprcyend - tlprcystart) >> pdy);
			
			if (resno == 0) {
				tlcbgxstart = tlprcxstart;
				tlcbgystart = tlprcystart;
				brcbgxend = brprcxend;
				brcbgyend = brprcyend;
				cbgwidthexpn = pdx;
				cbgheightexpn = pdy;
			} else {
				tlcbgxstart = int_ceildivpow2(tlprcxstart, 1);
				tlcbgystart = int_ceildivpow2(tlprcystart, 1);
				brcbgxend = int_ceildivpow2(brprcxend, 1);
				brcbgyend = int_ceildivpow2(brprcyend, 1);
				cbgwidthexpn = pdx - 1;
				cbgheightexpn = pdy - 1;
			}
			
			cblkwidthexpn = int_min(tccp->cblkw, cbgwidthexpn);
			cblkheightexpn = int_min(tccp->cblkh, cbgheightexpn);
			
			for (bandno = 0; bandno < res->numbands; bandno++) {
				int x0b, y0b;
				int gain, numbps;
				opj_stepsize_t *ss = NULL;
				
				opj_tcd_band_t *band = &res->bands[bandno];
				band->bandno = resno == 0 ? 0 : bandno + 1;
				x0b = (band->bandno == 1) || (band->bandno == 3) ? 1 : 0;
				y0b = (band->bandno == 2) || (band->bandno == 3) ? 1 : 0;
				
				if (band->bandno == 0) {
					/* band border (global) */
					band->x0 = int_ceildivpow2(tilec->x0, levelno);
					band->y0 = int_ceildivpow2(tilec->y0, levelno);
					band->x1 = int_ceildivpow2(tilec->x1, levelno);
					band->y1 = int_ceildivpow2(tilec->y1, levelno);
				} else {
					/* band border (global) */
					band->x0 = int_ceildivpow2(tilec->x0 - (1 << levelno) * x0b, levelno + 1);
					band->y0 = int_ceildivpow2(tilec->y0 - (1 << levelno) * y0b, levelno + 1);
					band->x1 = int_ceildivpow2(tilec->x1 - (1 << levelno) * x0b, levelno + 1);
					band->y1 = int_ceildivpow2(tilec->y1 - (1 << levelno) * y0b, levelno + 1);
				}
				
				ss = &tccp->stepsizes[resno == 0 ? 0 : 3 * (resno - 1) + bandno + 1];
				gain = tccp->qmfbid == 0 ? dwt_getgain_real(band->bandno) : dwt_getgain(band->bandno);
				numbps = image->comps[compno].prec + gain;
				band->stepsize = (float)(((1.0 + ss->mant / 2048.0) * pow(2.0, numbps - ss->expn)) * 0.5);
				band->numbps = ss->expn + tccp->numgbits - 1;	/* WHY -1 ? */
				
				band->precincts = (opj_tcd_precinct_t *) opj_malloc(res->pw * res->ph * sizeof(opj_tcd_precinct_t));
				
				for (precno = 0; precno < res->pw * res->ph; precno++) {
					int tlcblkxstart, tlcblkystart, brcblkxend, brcblkyend;
					int cbgxstart = tlcbgxstart + (precno % res->pw) * (1 << cbgwidthexpn);
					int cbgystart = tlcbgystart + (precno / res->pw) * (1 << cbgheightexpn);
					int cbgxend = cbgxstart + (1 << cbgwidthexpn);
					int cbgyend = cbgystart + (1 << cbgheightexpn);
					
					opj_tcd_precinct_t *prc = &band->precincts[precno];
					/* precinct size (global) */
					prc->x0 = int_max(cbgxstart, band->x0);
					prc->y0 = int_max(cbgystart, band->y0);
					prc->x1 = int_min(cbgxend, band->x1);
					prc->y1 = int_min(cbgyend, band->y1);
					
					tlcblkxstart = int_floordivpow2(prc->x0, cblkwidthexpn) << cblkwidthexpn;
					tlcblkystart = int_floordivpow2(prc->y0, cblkheightexpn) << cblkheightexpn;
					brcblkxend = int_ceildivpow2(prc->x1, cblkwidthexpn) << cblkwidthexpn;
					brcblkyend = int_ceildivpow2(prc->y1, cblkheightexpn) << cblkheightexpn;
					prc->cw = (brcblkxend - tlcblkxstart) >> cblkwidthexpn;
					prc->ch = (brcblkyend - tlcblkystart) >> cblkheightexpn;

					prc->cblks.dec = (opj_tcd_cblk_dec_t*) opj_malloc(prc->cw * prc->ch * sizeof(opj_tcd_cblk_dec_t));

					prc->incltree = tgt_create(prc->cw, prc->ch);
					prc->imsbtree = tgt_create(prc->cw, prc->ch);
					
					for (cblkno = 0; cblkno < prc->cw * prc->ch; cblkno++) {
						int cblkxstart = tlcblkxstart + (cblkno % prc->cw) * (1 << cblkwidthexpn);
						int cblkystart = tlcblkystart + (cblkno / prc->cw) * (1 << cblkheightexpn);
						int cblkxend = cblkxstart + (1 << cblkwidthexpn);
						int cblkyend = cblkystart + (1 << cblkheightexpn);					

						opj_tcd_cblk_dec_t* cblk = &prc->cblks.dec[cblkno];
						cblk->data = NULL;
						cblk->segs = NULL;
						/* code-block size (global) */
						cblk->x0 = int_max(cblkxstart, prc->x0);
						cblk->y0 = int_max(cblkystart, prc->y0);
						cblk->x1 = int_min(cblkxend, prc->x1);
						cblk->y1 = int_min(cblkyend, prc->y1);
						cblk->numsegs = 0;
            cblk->numbps = 0; /* EMSCRIPTEN: Prevent SAFE_HEAP warnings */
					}
				} /* precno */
			} /* bandno */
		} /* resno */
	} /* compno */
	/* tcd_dump(stdout, tcd, &tcd->tcd_image); */
}