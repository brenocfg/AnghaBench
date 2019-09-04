#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int numlayers; int csty; int POC; int numpocs; TYPE_4__* tccps; TYPE_5__* pocs; int /*<<< orphan*/  mct; int /*<<< orphan*/  prg; int /*<<< orphan*/ * rates; int /*<<< orphan*/ * distoratio; } ;
typedef  TYPE_3__ opj_tcp_t ;
struct TYPE_17__ {int csty; int numresolutions; int qmfbid; int numgbits; int* prcw; int* prch; scalar_t__ roishift; int /*<<< orphan*/  qntsty; int /*<<< orphan*/  cblksty; void* cblkh; void* cblkw; } ;
typedef  TYPE_4__ opj_tccp_t ;
struct TYPE_18__ {int tile; int /*<<< orphan*/  prg1; int /*<<< orphan*/  compno1; int /*<<< orphan*/  resno1; int /*<<< orphan*/  layno1; int /*<<< orphan*/  compno0; int /*<<< orphan*/  resno0; } ;
typedef  TYPE_5__ opj_poc_t ;
struct TYPE_19__ {TYPE_9__* cp; } ;
typedef  TYPE_6__ opj_j2k_t ;
struct TYPE_20__ {int numcomps; TYPE_2__* comps; scalar_t__ y1; scalar_t__ x1; } ;
typedef  TYPE_7__ opj_image_t ;
struct TYPE_21__ {int tcp_numlayers; int numresolution; int csty; int numpocs; int cblockw_init; int cblockh_init; int roi_compno; int res_spec; int* prcw_init; int* prch_init; scalar_t__ cp_cinema; scalar_t__ roi_shift; scalar_t__ irreversible; int /*<<< orphan*/  mode; TYPE_1__* POC; int /*<<< orphan*/  tcp_mct; int /*<<< orphan*/  prog_order; int /*<<< orphan*/ * tcp_rates; int /*<<< orphan*/ * tcp_distoratio; int /*<<< orphan*/  tp_flag; scalar_t__ tp_on; scalar_t__ tile_size_on; int /*<<< orphan*/  cp_comment; scalar_t__ cp_ty0; scalar_t__ cp_tx0; scalar_t__ cp_tdy; scalar_t__ cp_tdx; int /*<<< orphan*/  cp_matrice; scalar_t__ cp_fixed_quality; int /*<<< orphan*/  cp_fixed_alloc; int /*<<< orphan*/  cp_disto_alloc; int /*<<< orphan*/  cp_rsiz; int /*<<< orphan*/  max_comp_size; } ;
typedef  TYPE_8__ opj_cparameters_t ;
struct TYPE_22__ {int tw; int th; int* matrice; char* comment; int tp_on; scalar_t__ fixed_quality; scalar_t__ cinema; TYPE_3__* tcps; scalar_t__ img_size; int /*<<< orphan*/  tp_flag; scalar_t__ ty0; scalar_t__ tdy; scalar_t__ tx0; scalar_t__ tdx; int /*<<< orphan*/  fixed_alloc; int /*<<< orphan*/  disto_alloc; int /*<<< orphan*/  rsiz; int /*<<< orphan*/  max_comp_size; } ;
typedef  TYPE_9__ opj_cp_t ;
struct TYPE_15__ {int w; int h; int prec; } ;
struct TYPE_14__ {int tile; int /*<<< orphan*/  prg1; int /*<<< orphan*/  compno1; int /*<<< orphan*/  resno1; int /*<<< orphan*/  layno1; int /*<<< orphan*/  compno0; int /*<<< orphan*/  resno0; } ;

/* Variables and functions */
 int J2K_CCP_CSTY_PRT ; 
 int /*<<< orphan*/  J2K_CCP_QNTSTY_NOQNT ; 
 int /*<<< orphan*/  J2K_CCP_QNTSTY_SEQNT ; 
 int /*<<< orphan*/  dwt_calc_explicit_stepsizes (TYPE_4__*,int) ; 
 void* int_ceildiv (scalar_t__,scalar_t__) ; 
 void* int_floorlog2 (int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ opj_calloc (int,int) ; 
 scalar_t__ opj_malloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

void j2k_setup_encoder(opj_j2k_t *j2k, opj_cparameters_t *parameters, opj_image_t *image) {
	int i, j, tileno, numpocs_tile;
	opj_cp_t *cp = NULL;

	if(!j2k || !parameters || ! image) {
		return;
	}

	/* create and initialize the coding parameters structure */
	cp = (opj_cp_t*) opj_calloc(1, sizeof(opj_cp_t));

	/* keep a link to cp so that we can destroy it later in j2k_destroy_compress */
	j2k->cp = cp;

	/* set default values for cp */
	cp->tw = 1;
	cp->th = 1;

	/* 
	copy user encoding parameters 
	*/
	cp->cinema = parameters->cp_cinema;
	cp->max_comp_size =	parameters->max_comp_size;
	cp->rsiz   = parameters->cp_rsiz;
	cp->disto_alloc = parameters->cp_disto_alloc;
	cp->fixed_alloc = parameters->cp_fixed_alloc;
	cp->fixed_quality = parameters->cp_fixed_quality;

	/* mod fixed_quality */
	if(parameters->cp_matrice) {
		size_t array_size = parameters->tcp_numlayers * parameters->numresolution * 3 * sizeof(int);
		cp->matrice = (int *) opj_malloc(array_size);
		memcpy(cp->matrice, parameters->cp_matrice, array_size);
	}

	/* tiles */
	cp->tdx = parameters->cp_tdx;
	cp->tdy = parameters->cp_tdy;

	/* tile offset */
	cp->tx0 = parameters->cp_tx0;
	cp->ty0 = parameters->cp_ty0;

	/* comment string */
	if(parameters->cp_comment) {
		cp->comment = (char*)opj_malloc(strlen(parameters->cp_comment) + 1);
		if(cp->comment) {
			strcpy(cp->comment, parameters->cp_comment);
		}
	}

	/*
	calculate other encoding parameters
	*/

	if (parameters->tile_size_on) {
		cp->tw = int_ceildiv(image->x1 - cp->tx0, cp->tdx);
		cp->th = int_ceildiv(image->y1 - cp->ty0, cp->tdy);
	} else {
		cp->tdx = image->x1 - cp->tx0;
		cp->tdy = image->y1 - cp->ty0;
	}

	if(parameters->tp_on){
		cp->tp_flag = parameters->tp_flag;
		cp->tp_on = 1;
	}
	
	cp->img_size = 0;
	for(i=0;i<image->numcomps ;i++){
	cp->img_size += (image->comps[i].w *image->comps[i].h * image->comps[i].prec);
	}


#ifdef USE_JPWL
	/*
	calculate JPWL encoding parameters
	*/

	if (parameters->jpwl_epc_on) {
		int i;

		/* set JPWL on */
		cp->epc_on = true;
		cp->info_on = false; /* no informative technique */

		/* set EPB on */
		if ((parameters->jpwl_hprot_MH > 0) || (parameters->jpwl_hprot_TPH[0] > 0)) {
			cp->epb_on = true;
			
			cp->hprot_MH = parameters->jpwl_hprot_MH;
			for (i = 0; i < JPWL_MAX_NO_TILESPECS; i++) {
				cp->hprot_TPH_tileno[i] = parameters->jpwl_hprot_TPH_tileno[i];
				cp->hprot_TPH[i] = parameters->jpwl_hprot_TPH[i];
			}
			/* if tile specs are not specified, copy MH specs */
			if (cp->hprot_TPH[0] == -1) {
				cp->hprot_TPH_tileno[0] = 0;
				cp->hprot_TPH[0] = parameters->jpwl_hprot_MH;
			}
			for (i = 0; i < JPWL_MAX_NO_PACKSPECS; i++) {
				cp->pprot_tileno[i] = parameters->jpwl_pprot_tileno[i];
				cp->pprot_packno[i] = parameters->jpwl_pprot_packno[i];
				cp->pprot[i] = parameters->jpwl_pprot[i];
			}
		}

		/* set ESD writing */
		if ((parameters->jpwl_sens_size == 1) || (parameters->jpwl_sens_size == 2)) {
			cp->esd_on = true;

			cp->sens_size = parameters->jpwl_sens_size;
			cp->sens_addr = parameters->jpwl_sens_addr;
			cp->sens_range = parameters->jpwl_sens_range;

			cp->sens_MH = parameters->jpwl_sens_MH;
			for (i = 0; i < JPWL_MAX_NO_TILESPECS; i++) {
				cp->sens_TPH_tileno[i] = parameters->jpwl_sens_TPH_tileno[i];
				cp->sens_TPH[i] = parameters->jpwl_sens_TPH[i];
			}
		}

		/* always set RED writing to false: we are at the encoder */
		cp->red_on = false;

	} else {
		cp->epc_on = false;
	}
#endif /* USE_JPWL */


	/* initialize the mutiple tiles */
	/* ---------------------------- */
	cp->tcps = (opj_tcp_t*) opj_calloc(cp->tw * cp->th, sizeof(opj_tcp_t));

	for (tileno = 0; tileno < cp->tw * cp->th; tileno++) {
		opj_tcp_t *tcp = &cp->tcps[tileno];
		tcp->numlayers = parameters->tcp_numlayers;
		for (j = 0; j < tcp->numlayers; j++) {
			if(cp->cinema){
				if (cp->fixed_quality) {
					tcp->distoratio[j] = parameters->tcp_distoratio[j];
				}
				tcp->rates[j] = parameters->tcp_rates[j];
			}else{
				if (cp->fixed_quality) {	/* add fixed_quality */
					tcp->distoratio[j] = parameters->tcp_distoratio[j];
				} else {
					tcp->rates[j] = parameters->tcp_rates[j];
				}
			}
		}
		tcp->csty = parameters->csty;
		tcp->prg = parameters->prog_order;
		tcp->mct = parameters->tcp_mct; 

		numpocs_tile = 0;
		tcp->POC = 0;
		if (parameters->numpocs) {
			/* initialisation of POC */
			tcp->POC = 1;
			for (i = 0; i < parameters->numpocs; i++) {
				if((tileno == parameters->POC[i].tile - 1) || (parameters->POC[i].tile == -1)) {
					opj_poc_t *tcp_poc = &tcp->pocs[numpocs_tile];
					tcp_poc->resno0		= parameters->POC[numpocs_tile].resno0;
					tcp_poc->compno0	= parameters->POC[numpocs_tile].compno0;
					tcp_poc->layno1		= parameters->POC[numpocs_tile].layno1;
					tcp_poc->resno1		= parameters->POC[numpocs_tile].resno1;
					tcp_poc->compno1	= parameters->POC[numpocs_tile].compno1;
					tcp_poc->prg1		= parameters->POC[numpocs_tile].prg1;
					tcp_poc->tile		= parameters->POC[numpocs_tile].tile;
					numpocs_tile++;
				}
			}
			tcp->numpocs = numpocs_tile -1 ;
		}else{ 
			tcp->numpocs = 0;
		}

		tcp->tccps = (opj_tccp_t*) opj_calloc(image->numcomps, sizeof(opj_tccp_t));

		for (i = 0; i < image->numcomps; i++) {
			opj_tccp_t *tccp = &tcp->tccps[i];
			tccp->csty = parameters->csty & 0x01;	/* 0 => one precinct || 1 => custom precinct  */
			tccp->numresolutions = parameters->numresolution;
			tccp->cblkw = int_floorlog2(parameters->cblockw_init);
			tccp->cblkh = int_floorlog2(parameters->cblockh_init);
			tccp->cblksty = parameters->mode;
			tccp->qmfbid = parameters->irreversible ? 0 : 1;
			tccp->qntsty = parameters->irreversible ? J2K_CCP_QNTSTY_SEQNT : J2K_CCP_QNTSTY_NOQNT;
			tccp->numgbits = 2;
			if (i == parameters->roi_compno) {
				tccp->roishift = parameters->roi_shift;
			} else {
				tccp->roishift = 0;
			}

			if(parameters->cp_cinema)
			{
				//Precinct size for lowest frequency subband=128
				tccp->prcw[0] = 7;
				tccp->prch[0] = 7;
				//Precinct size at all other resolutions = 256
				for (j = 1; j < tccp->numresolutions; j++) {
					tccp->prcw[j] = 8;
					tccp->prch[j] = 8;
				}
			}else{
				if (parameters->csty & J2K_CCP_CSTY_PRT) {
					int p = 0;
					for (j = tccp->numresolutions - 1; j >= 0; j--) {
						if (p < parameters->res_spec) {
							
							if (parameters->prcw_init[p] < 1) {
								tccp->prcw[j] = 1;
							} else {
								tccp->prcw[j] = int_floorlog2(parameters->prcw_init[p]);
							}
							
							if (parameters->prch_init[p] < 1) {
								tccp->prch[j] = 1;
							}else {
								tccp->prch[j] = int_floorlog2(parameters->prch_init[p]);
							}

						} else {
							int res_spec = parameters->res_spec;
							int size_prcw = parameters->prcw_init[res_spec - 1] >> (p - (res_spec - 1));
							int size_prch = parameters->prch_init[res_spec - 1] >> (p - (res_spec - 1));
							
							if (size_prcw < 1) {
								tccp->prcw[j] = 1;
							} else {
								tccp->prcw[j] = int_floorlog2(size_prcw);
							}
							
							if (size_prch < 1) {
								tccp->prch[j] = 1;
							} else {
								tccp->prch[j] = int_floorlog2(size_prch);
							}
						}
						p++;
						/*printf("\nsize precinct for level %d : %d,%d\n", j,tccp->prcw[j], tccp->prch[j]); */
					}	//end for
				} else {
					for (j = 0; j < tccp->numresolutions; j++) {
						tccp->prcw[j] = 15;
						tccp->prch[j] = 15;
					}
				}
			}

			dwt_calc_explicit_stepsizes(tccp, image->comps[i].prec);
		}
	}
}