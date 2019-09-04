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

/* Type definitions */
struct TYPE_17__ {int numlayers; int* rates; } ;
typedef  TYPE_5__ opj_tcp_t ;
struct TYPE_18__ {int cur_tp_num; TYPE_4__* tcd_image; int /*<<< orphan*/  tp_num; } ;
typedef  TYPE_6__ opj_tcd_t ;
struct TYPE_19__ {int cur_tp_num; size_t curtileno; int sod_start; scalar_t__ pos_correction; scalar_t__ sot_start; scalar_t__ tlm_start; TYPE_9__* cstr_info; int /*<<< orphan*/  tp_num; int /*<<< orphan*/ * cio; TYPE_8__* cp; } ;
typedef  TYPE_7__ opj_j2k_t ;
struct TYPE_20__ {int th; int tw; scalar_t__ cinema; TYPE_5__* tcps; } ;
typedef  TYPE_8__ opj_cp_t ;
struct TYPE_21__ {int packno; TYPE_2__* tile; } ;
typedef  TYPE_9__ opj_codestream_info_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_16__ {TYPE_3__* tiles; } ;
struct TYPE_15__ {scalar_t__ packno; } ;
struct TYPE_14__ {size_t tileno; TYPE_1__* packet; scalar_t__ end_header; } ;
struct TYPE_13__ {scalar_t__ end_pos; scalar_t__ start_pos; } ;

/* Variables and functions */
 int J2K_MS_SOD ; 
 int /*<<< orphan*/  cio_getbp (int /*<<< orphan*/ *) ; 
 scalar_t__ cio_numbytesleft (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cio_seek (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cio_write (int /*<<< orphan*/ *,int,int) ; 
 int tcd_encode_tile (TYPE_6__*,size_t,int /*<<< orphan*/ ,scalar_t__,TYPE_9__*) ; 

__attribute__((used)) static void j2k_write_sod(opj_j2k_t *j2k, void *tile_coder) {
	int l, layno;
	int totlen;
	opj_tcp_t *tcp = NULL;
	opj_codestream_info_t *cstr_info = NULL;
	
	opj_tcd_t *tcd = (opj_tcd_t*)tile_coder;	/* cast is needed because of conflicts in header inclusions */
	opj_cp_t *cp = j2k->cp;
	opj_cio_t *cio = j2k->cio;

	tcd->tp_num = j2k->tp_num ;
	tcd->cur_tp_num = j2k->cur_tp_num;
	
	cio_write(cio, J2K_MS_SOD, 2);
	if (j2k->curtileno == 0) {
		j2k->sod_start = cio_tell(cio) + j2k->pos_correction;
	}

	/* INDEX >> */
	cstr_info = j2k->cstr_info;
	if (cstr_info) {
		if (!j2k->cur_tp_num ) {
			cstr_info->tile[j2k->curtileno].end_header = cio_tell(cio) + j2k->pos_correction - 1;
			j2k->cstr_info->tile[j2k->curtileno].tileno = j2k->curtileno;
		}
		else{
			if(cstr_info->tile[j2k->curtileno].packet[cstr_info->packno - 1].end_pos < cio_tell(cio))
				cstr_info->tile[j2k->curtileno].packet[cstr_info->packno].start_pos = cio_tell(cio);
		}
		/* UniPG>> */
#ifdef USE_JPWL
		/* update markers struct */
		j2k_add_marker(j2k->cstr_info, J2K_MS_SOD, j2k->sod_start, 2);
#endif /* USE_JPWL */
		/* <<UniPG */
	}
	/* << INDEX */
	
	tcp = &cp->tcps[j2k->curtileno];
	for (layno = 0; layno < tcp->numlayers; layno++) {
		if (tcp->rates[layno]>(j2k->sod_start / (cp->th * cp->tw))) {
			tcp->rates[layno]-=(j2k->sod_start / (cp->th * cp->tw));
		} else if (tcp->rates[layno]) {
			tcp->rates[layno]=1;
		}
	}
	if(j2k->cur_tp_num == 0){
		tcd->tcd_image->tiles->packno = 0;
		if(cstr_info)
			cstr_info->packno = 0;
	}
	
	l = tcd_encode_tile(tcd, j2k->curtileno, cio_getbp(cio), cio_numbytesleft(cio) - 2, cstr_info);
	
	/* Writing Psot in SOT marker */
	totlen = cio_tell(cio) + l - j2k->sot_start;
	cio_seek(cio, j2k->sot_start + 6);
	cio_write(cio, totlen, 4);
	cio_seek(cio, j2k->sot_start + totlen);
	/* Writing Ttlm and Ptlm in TLM marker */
	if(cp->cinema){
		cio_seek(cio, j2k->tlm_start + 6 + (5*j2k->cur_tp_num));
		cio_write(cio, j2k->curtileno, 1);
		cio_write(cio, totlen, 4);
	}
	cio_seek(cio, j2k->sot_start + totlen);
}