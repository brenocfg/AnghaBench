#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_12__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
struct TYPE_32__ {int /*<<< orphan*/  numlayers; TYPE_9__* tccps; scalar_t__ mct; } ;
typedef  TYPE_4__ opj_tcp_t ;
struct TYPE_33__ {int numresolutions; int x1; int x0; int y0; int y1; int* data; TYPE_8__* resolutions; } ;
typedef  TYPE_5__ opj_tcd_tilecomp_t ;
struct TYPE_34__ {int numcomps; TYPE_5__* comps; } ;
typedef  TYPE_6__ opj_tcd_tile_t ;
struct TYPE_35__ {int tcd_tileno; scalar_t__ cur_tp_num; void* encoding_time; int cur_totnum_tp; int /*<<< orphan*/  cinfo; int /*<<< orphan*/  cur_pino; int /*<<< orphan*/  tp_pos; int /*<<< orphan*/  tp_num; TYPE_11__* cp; TYPE_4__* tcp; TYPE_6__* tcd_tile; TYPE_3__* tcd_image; TYPE_10__* image; } ;
typedef  TYPE_7__ opj_tcd_t ;
struct TYPE_36__ {int pw; int ph; } ;
typedef  TYPE_8__ opj_tcd_resolution_t ;
struct TYPE_37__ {int qmfbid; int /*<<< orphan*/ * prch; int /*<<< orphan*/ * prcw; } ;
typedef  TYPE_9__ opj_tccp_t ;
typedef  int /*<<< orphan*/  opj_t2_t ;
typedef  int /*<<< orphan*/  opj_t1_t ;
typedef  int /*<<< orphan*/  opj_packet_info_t ;
struct TYPE_26__ {TYPE_2__* comps; scalar_t__ x0; scalar_t__ x1; scalar_t__ y0; } ;
typedef  TYPE_10__ opj_image_t ;
struct TYPE_27__ {scalar_t__ fixed_quality; scalar_t__ disto_alloc; TYPE_4__* tcps; } ;
typedef  TYPE_11__ opj_cp_t ;
struct TYPE_28__ {int numcomps; int numlayers; int index_write; TYPE_1__* tile; } ;
typedef  TYPE_12__ opj_codestream_info_t ;
struct TYPE_31__ {TYPE_6__* tiles; } ;
struct TYPE_30__ {int prec; int* data; int /*<<< orphan*/  dx; int /*<<< orphan*/  dy; scalar_t__ sgnd; } ;
struct TYPE_29__ {int* pw; int* ph; int /*<<< orphan*/ * packet; int /*<<< orphan*/ * pdy; int /*<<< orphan*/ * pdx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_INFO ; 
 int /*<<< orphan*/  FINAL_PASS ; 
 int /*<<< orphan*/  dwt_encode (TYPE_5__*) ; 
 int /*<<< orphan*/  dwt_encode_real (TYPE_5__*) ; 
 int int_ceildiv (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mct_encode (int*,int*,int*,int) ; 
 int /*<<< orphan*/  mct_encode_real (int*,int*,int*,int) ; 
 int /*<<< orphan*/  opj_aligned_free (int*) ; 
 scalar_t__ opj_calloc (int,int) ; 
 void* opj_clock () ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/ * t1_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t1_encode_cblks (int /*<<< orphan*/ *,TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/ * t2_create (int /*<<< orphan*/ ,TYPE_10__*,TYPE_11__*) ; 
 int /*<<< orphan*/  t2_destroy (int /*<<< orphan*/ *) ; 
 int t2_encode_packets (int /*<<< orphan*/ *,int,TYPE_6__*,int /*<<< orphan*/ ,unsigned char*,int,TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcd_rateallocate (TYPE_7__*,unsigned char*,int,TYPE_12__*) ; 
 int /*<<< orphan*/  tcd_rateallocate_fixed (TYPE_7__*) ; 

int tcd_encode_tile(opj_tcd_t *tcd, int tileno, unsigned char *dest, int len, opj_codestream_info_t *cstr_info) {
	int compno;
	int l, i, numpacks = 0;
	opj_tcd_tile_t *tile = NULL;
	opj_tcp_t *tcd_tcp = NULL;
	opj_cp_t *cp = NULL;

	opj_tcp_t *tcp = &tcd->cp->tcps[0];
	opj_tccp_t *tccp = &tcp->tccps[0];
	opj_image_t *image = tcd->image;
	
	opj_t1_t *t1 = NULL;		/* T1 component */
	opj_t2_t *t2 = NULL;		/* T2 component */

	tcd->tcd_tileno = tileno;
	tcd->tcd_tile = tcd->tcd_image->tiles;
	tcd->tcp = &tcd->cp->tcps[tileno];

	tile = tcd->tcd_tile;
	tcd_tcp = tcd->tcp;
	cp = tcd->cp;

	if(tcd->cur_tp_num == 0){
		tcd->encoding_time = opj_clock();	/* time needed to encode a tile */
		/* INDEX >> "Precinct_nb_X et Precinct_nb_Y" */
		if(cstr_info) {
			opj_tcd_tilecomp_t *tilec_idx = &tile->comps[0];	/* based on component 0 */
			for (i = 0; i < tilec_idx->numresolutions; i++) {
				opj_tcd_resolution_t *res_idx = &tilec_idx->resolutions[i];
				
				cstr_info->tile[tileno].pw[i] = res_idx->pw;
				cstr_info->tile[tileno].ph[i] = res_idx->ph;
				
				numpacks += res_idx->pw * res_idx->ph;
				
				cstr_info->tile[tileno].pdx[i] = tccp->prcw[i];
				cstr_info->tile[tileno].pdy[i] = tccp->prch[i];
			}
			cstr_info->tile[tileno].packet = (opj_packet_info_t*) opj_calloc(cstr_info->numcomps * cstr_info->numlayers * numpacks, sizeof(opj_packet_info_t));
		}
		/* << INDEX */
		
		/*---------------TILE-------------------*/
		
		for (compno = 0; compno < tile->numcomps; compno++) {
			int x, y;
			
			int adjust = image->comps[compno].sgnd ? 0 : 1 << (image->comps[compno].prec - 1);
			int offset_x = int_ceildiv(image->x0, image->comps[compno].dx);
			int offset_y = int_ceildiv(image->y0, image->comps[compno].dy);
			
			opj_tcd_tilecomp_t *tilec = &tile->comps[compno];
			int tw = tilec->x1 - tilec->x0;
			int w = int_ceildiv(image->x1 - image->x0, image->comps[compno].dx);
			
			/* extract tile data */
			
			if (tcd_tcp->tccps[compno].qmfbid == 1) {
				for (y = tilec->y0; y < tilec->y1; y++) {
					/* start of the src tile scanline */
					int *data = &image->comps[compno].data[(tilec->x0 - offset_x) + (y - offset_y) * w];
					/* start of the dst tile scanline */
					int *tile_data = &tilec->data[(y - tilec->y0) * tw];
					for (x = tilec->x0; x < tilec->x1; x++) {
						*tile_data++ = *data++ - adjust;
					}
				}
			} else if (tcd_tcp->tccps[compno].qmfbid == 0) {
				for (y = tilec->y0; y < tilec->y1; y++) {
					/* start of the src tile scanline */
					int *data = &image->comps[compno].data[(tilec->x0 - offset_x) + (y - offset_y) * w];
					/* start of the dst tile scanline */
					int *tile_data = &tilec->data[(y - tilec->y0) * tw];
					for (x = tilec->x0; x < tilec->x1; x++) {
						*tile_data++ = (*data++ - adjust) << 11;
					}
					
				}
			}
		}
		
		/*----------------MCT-------------------*/
		if (tcd_tcp->mct) {
			int samples = (tile->comps[0].x1 - tile->comps[0].x0) * (tile->comps[0].y1 - tile->comps[0].y0);
			if (tcd_tcp->tccps[0].qmfbid == 0) {
				mct_encode_real(tile->comps[0].data, tile->comps[1].data, tile->comps[2].data, samples);
			} else {
				mct_encode(tile->comps[0].data, tile->comps[1].data, tile->comps[2].data, samples);
			}
		}
		
		/*----------------DWT---------------------*/
		
		for (compno = 0; compno < tile->numcomps; compno++) {
			opj_tcd_tilecomp_t *tilec = &tile->comps[compno];
			if (tcd_tcp->tccps[compno].qmfbid == 1) {
				dwt_encode(tilec);
			} else if (tcd_tcp->tccps[compno].qmfbid == 0) {
				dwt_encode_real(tilec);
			}
		}
		
		/*------------------TIER1-----------------*/
		t1 = t1_create(tcd->cinfo);
		t1_encode_cblks(t1, tile, tcd_tcp);
		t1_destroy(t1);
		
		/*-----------RATE-ALLOCATE------------------*/
		
		/* INDEX */
		if(cstr_info) {
			cstr_info->index_write = 0;
		}
		if (cp->disto_alloc || cp->fixed_quality) {	/* fixed_quality */
			/* Normal Rate/distortion allocation */
			tcd_rateallocate(tcd, dest, len, cstr_info);
		} else {
			/* Fixed layer allocation */
			tcd_rateallocate_fixed(tcd);
		}
	}
	/*--------------TIER2------------------*/

	/* INDEX */
	if(cstr_info) {
		cstr_info->index_write = 1;
	}

	t2 = t2_create(tcd->cinfo, image, cp);
	l = t2_encode_packets(t2,tileno, tile, tcd_tcp->numlayers, dest, len, cstr_info,tcd->tp_num,tcd->tp_pos,tcd->cur_pino,FINAL_PASS,tcd->cur_totnum_tp);
	t2_destroy(t2);
	
	/*---------------CLEAN-------------------*/

	
	if(tcd->cur_tp_num == tcd->cur_totnum_tp - 1){
		tcd->encoding_time = opj_clock() - tcd->encoding_time;
		opj_event_msg(tcd->cinfo, EVT_INFO, "- tile encoded in %f s\n", tcd->encoding_time);

		/* cleaning memory */
		for (compno = 0; compno < tile->numcomps; compno++) {
			opj_tcd_tilecomp_t *tilec = &tile->comps[compno];
			opj_aligned_free(tilec->data);
		}
	}

	return l;
}