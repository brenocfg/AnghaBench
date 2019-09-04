#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_tile_info_t ;
struct TYPE_10__ {int first; int /*<<< orphan*/ * tccps; scalar_t__ numpocs; scalar_t__ POC; } ;
typedef  TYPE_2__ opj_tcp_t ;
typedef  int /*<<< orphan*/  opj_tccp_t ;
struct TYPE_11__ {unsigned char** tile_data; int* tile_len; TYPE_7__* cstr_info; int /*<<< orphan*/  state; TYPE_1__* default_tcp; int /*<<< orphan*/  cinfo; TYPE_6__* cp; TYPE_4__* image; int /*<<< orphan*/ * cio; } ;
typedef  TYPE_3__ opj_j2k_t ;
struct TYPE_12__ {int numcomps; void* y0; void* y1; void* x0; void* x1; TYPE_5__* comps; } ;
typedef  TYPE_4__ opj_image_t ;
struct TYPE_13__ {int prec; int sgnd; int /*<<< orphan*/  factor; scalar_t__ resno_decoded; void* dy; void* dx; } ;
typedef  TYPE_5__ opj_image_comp_t ;
struct TYPE_14__ {int tw; int th; int* tileno; void* ty0; void* tx0; void* tdy; void* tdx; TYPE_2__* tcps; scalar_t__ ppm_store; scalar_t__ ppm_previous; int /*<<< orphan*/ * ppm_data_first; int /*<<< orphan*/ * ppm_data; scalar_t__ ppm; scalar_t__ tileno_size; int /*<<< orphan*/  reduce; } ;
typedef  TYPE_6__ opj_cp_t ;
struct TYPE_15__ {int numcomps; int tw; int th; int /*<<< orphan*/ * tile; void* tile_Oy; void* tile_Ox; void* tile_y; void* tile_x; void* image_h; void* image_w; } ;
typedef  TYPE_7__ opj_codestream_info_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_9__ {int /*<<< orphan*/ * tccps; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  J2K_STATE_MH ; 
 void* cio_read (int /*<<< orphan*/ *,int) ; 
 void* int_ceildiv (void*,void*) ; 
 scalar_t__ opj_calloc (int,int) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*,void*,void*,void*) ; 
 scalar_t__ opj_malloc (int) ; 

__attribute__((used)) static void j2k_read_siz(opj_j2k_t *j2k) {
	int len, i;
	
	opj_cio_t *cio = j2k->cio;
	opj_image_t *image = j2k->image;
	opj_cp_t *cp = j2k->cp;
	
	len = cio_read(cio, 2);			/* Lsiz */
	cio_read(cio, 2);				/* Rsiz (capabilities) */
	image->x1 = cio_read(cio, 4);	/* Xsiz */
	image->y1 = cio_read(cio, 4);	/* Ysiz */
	image->x0 = cio_read(cio, 4);	/* X0siz */
	image->y0 = cio_read(cio, 4);	/* Y0siz */
	cp->tdx = cio_read(cio, 4);		/* XTsiz */
	cp->tdy = cio_read(cio, 4);		/* YTsiz */
	cp->tx0 = cio_read(cio, 4);		/* XT0siz */
	cp->ty0 = cio_read(cio, 4);		/* YT0siz */
	
	if ((image->x0<0)||(image->x1<0)||(image->y0<0)||(image->y1<0)) {
		opj_event_msg(j2k->cinfo, EVT_ERROR,
									"%s: invalid image size (x0:%d, x1:%d, y0:%d, y1:%d)\n",
									image->x0,image->x1,image->y0,image->y1);
		return;
	}
	
	image->numcomps = cio_read(cio, 2);	/* Csiz */

#ifdef USE_JPWL
	if (j2k->cp->correct) {
		/* if JPWL is on, we check whether TX errors have damaged
		  too much the SIZ parameters */
		if (!(image->x1 * image->y1)) {
			opj_event_msg(j2k->cinfo, EVT_ERROR,
				"JPWL: bad image size (%d x %d)\n",
				image->x1, image->y1);
			if (!JPWL_ASSUME || JPWL_ASSUME) {
				opj_event_msg(j2k->cinfo, EVT_ERROR, "JPWL: giving up\n");
				return;
			}
		}
		if (image->numcomps != ((len - 38) / 3)) {
			opj_event_msg(j2k->cinfo, JPWL_ASSUME ? EVT_WARNING : EVT_ERROR,
				"JPWL: Csiz is %d => space in SIZ only for %d comps.!!!\n",
				image->numcomps, ((len - 38) / 3));
			if (!JPWL_ASSUME) {
				opj_event_msg(j2k->cinfo, EVT_ERROR, "JPWL: giving up\n");
				return;
			}
			/* we try to correct */
			opj_event_msg(j2k->cinfo, EVT_WARNING, "- trying to adjust this\n");
			if (image->numcomps < ((len - 38) / 3)) {
				len = 38 + 3 * image->numcomps;
				opj_event_msg(j2k->cinfo, EVT_WARNING, "- setting Lsiz to %d => HYPOTHESIS!!!\n",
					len);				
			} else {
				image->numcomps = ((len - 38) / 3);
				opj_event_msg(j2k->cinfo, EVT_WARNING, "- setting Csiz to %d => HYPOTHESIS!!!\n",
					image->numcomps);				
			}
		}

		/* update components number in the jpwl_exp_comps filed */
		cp->exp_comps = image->numcomps;
	}
#endif /* USE_JPWL */

	image->comps = (opj_image_comp_t*) opj_calloc(image->numcomps, sizeof(opj_image_comp_t));
	for (i = 0; i < image->numcomps; i++) {
		int tmp, w, h;
		tmp = cio_read(cio, 1);		/* Ssiz_i */
		image->comps[i].prec = (tmp & 0x7f) + 1;
		image->comps[i].sgnd = tmp >> 7;
		image->comps[i].dx = cio_read(cio, 1);	/* XRsiz_i */
		image->comps[i].dy = cio_read(cio, 1);	/* YRsiz_i */
		
#ifdef USE_JPWL
		if (j2k->cp->correct) {
		/* if JPWL is on, we check whether TX errors have damaged
			too much the SIZ parameters, again */
			if (!(image->comps[i].dx * image->comps[i].dy)) {
				opj_event_msg(j2k->cinfo, JPWL_ASSUME ? EVT_WARNING : EVT_ERROR,
					"JPWL: bad XRsiz_%d/YRsiz_%d (%d x %d)\n",
					i, i, image->comps[i].dx, image->comps[i].dy);
				if (!JPWL_ASSUME) {
					opj_event_msg(j2k->cinfo, EVT_ERROR, "JPWL: giving up\n");
					return;
				}
				/* we try to correct */
				opj_event_msg(j2k->cinfo, EVT_WARNING, "- trying to adjust them\n");
				if (!image->comps[i].dx) {
					image->comps[i].dx = 1;
					opj_event_msg(j2k->cinfo, EVT_WARNING, "- setting XRsiz_%d to %d => HYPOTHESIS!!!\n",
						i, image->comps[i].dx);
				}
				if (!image->comps[i].dy) {
					image->comps[i].dy = 1;
					opj_event_msg(j2k->cinfo, EVT_WARNING, "- setting YRsiz_%d to %d => HYPOTHESIS!!!\n",
						i, image->comps[i].dy);
				}
			}
			
		}
#endif /* USE_JPWL */

		/* TODO: unused ? */
		w = int_ceildiv(image->x1 - image->x0, image->comps[i].dx);
		h = int_ceildiv(image->y1 - image->y0, image->comps[i].dy);

		image->comps[i].resno_decoded = 0;	/* number of resolution decoded */
		image->comps[i].factor = cp->reduce; /* reducing factor per component */
	}
	
	cp->tw = int_ceildiv(image->x1 - cp->tx0, cp->tdx);
	cp->th = int_ceildiv(image->y1 - cp->ty0, cp->tdy);

#ifdef USE_JPWL
	if (j2k->cp->correct) {
		/* if JPWL is on, we check whether TX errors have damaged
		  too much the SIZ parameters */
		if ((cp->tw < 1) || (cp->th < 1) || (cp->tw > cp->max_tiles) || (cp->th > cp->max_tiles)) {
			opj_event_msg(j2k->cinfo, JPWL_ASSUME ? EVT_WARNING : EVT_ERROR,
				"JPWL: bad number of tiles (%d x %d)\n",
				cp->tw, cp->th);
			if (!JPWL_ASSUME) {
				opj_event_msg(j2k->cinfo, EVT_ERROR, "JPWL: giving up\n");
				return;
			}
			/* we try to correct */
			opj_event_msg(j2k->cinfo, EVT_WARNING, "- trying to adjust them\n");
			if (cp->tw < 1) {
				cp->tw= 1;
				opj_event_msg(j2k->cinfo, EVT_WARNING, "- setting %d tiles in x => HYPOTHESIS!!!\n",
					cp->tw);
			}
			if (cp->tw > cp->max_tiles) {
				cp->tw= 1;
				opj_event_msg(j2k->cinfo, EVT_WARNING, "- too large x, increase expectance of %d\n"
					"- setting %d tiles in x => HYPOTHESIS!!!\n",
					cp->max_tiles, cp->tw);
			}
			if (cp->th < 1) {
				cp->th= 1;
				opj_event_msg(j2k->cinfo, EVT_WARNING, "- setting %d tiles in y => HYPOTHESIS!!!\n",
					cp->th);
			}
			if (cp->th > cp->max_tiles) {
				cp->th= 1;
				opj_event_msg(j2k->cinfo, EVT_WARNING, "- too large y, increase expectance of %d to continue\n",
					"- setting %d tiles in y => HYPOTHESIS!!!\n",
					cp->max_tiles, cp->th);
			}
		}
	}
#endif /* USE_JPWL */

	cp->tcps = (opj_tcp_t*) opj_calloc(cp->tw * cp->th, sizeof(opj_tcp_t));
	cp->tileno = (int*) opj_malloc(cp->tw * cp->th * sizeof(int));
	cp->tileno_size = 0;
	
#ifdef USE_JPWL
	if (j2k->cp->correct) {
		if (!cp->tcps) {
			opj_event_msg(j2k->cinfo, JPWL_ASSUME ? EVT_WARNING : EVT_ERROR,
				"JPWL: could not alloc tcps field of cp\n");
			if (!JPWL_ASSUME || JPWL_ASSUME) {
				opj_event_msg(j2k->cinfo, EVT_ERROR, "JPWL: giving up\n");
				return;
			}
		}
	}
#endif /* USE_JPWL */

	for (i = 0; i < cp->tw * cp->th; i++) {
		cp->tcps[i].POC = 0;
		cp->tcps[i].numpocs = 0;
		cp->tcps[i].first = 1;
	}
	
	/* Initialization for PPM marker */
	cp->ppm = 0;
	cp->ppm_data = NULL;
	cp->ppm_data_first = NULL;
	cp->ppm_previous = 0;
	cp->ppm_store = 0;

	j2k->default_tcp->tccps = (opj_tccp_t*) opj_calloc(image->numcomps, sizeof(opj_tccp_t));
	for (i = 0; i < cp->tw * cp->th; i++) {
		cp->tcps[i].tccps = (opj_tccp_t*) opj_malloc(image->numcomps * sizeof(opj_tccp_t));
	}	
	j2k->tile_data = (unsigned char**) opj_calloc(cp->tw * cp->th, sizeof(unsigned char*));
	j2k->tile_len = (int*) opj_calloc(cp->tw * cp->th, sizeof(int));
	j2k->state = J2K_STATE_MH;

	/* Index */
	if (j2k->cstr_info) {
		opj_codestream_info_t *cstr_info = j2k->cstr_info;
		cstr_info->image_w = image->x1 - image->x0;
		cstr_info->image_h = image->y1 - image->y0;
		cstr_info->numcomps = image->numcomps;
		cstr_info->tw = cp->tw;
		cstr_info->th = cp->th;
		cstr_info->tile_x = cp->tdx;	
		cstr_info->tile_y = cp->tdy;	
		cstr_info->tile_Ox = cp->tx0;	
		cstr_info->tile_Oy = cp->ty0;			
		cstr_info->tile = (opj_tile_info_t*) opj_calloc(cp->tw * cp->th, sizeof(opj_tile_info_t));		
	}
}