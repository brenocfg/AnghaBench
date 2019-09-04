#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {void* tp_start_pos; void* tp_end_pos; } ;
typedef  TYPE_4__ opj_tp_info_t ;
struct TYPE_15__ {int first; int /*<<< orphan*/ * tccps; int /*<<< orphan*/ * ppt_data_first; int /*<<< orphan*/ * ppt_data; scalar_t__ ppt; } ;
typedef  TYPE_5__ opj_tcp_t ;
typedef  int /*<<< orphan*/  opj_tccp_t ;
struct TYPE_16__ {int curtileno; int cur_tp_num; int eot; TYPE_9__* default_tcp; TYPE_3__* image; TYPE_2__* cstr_info; int /*<<< orphan*/  state; int /*<<< orphan*/ * cio; TYPE_7__* cp; } ;
typedef  TYPE_6__ opj_j2k_t ;
struct TYPE_17__ {size_t tileno_size; int* tileno; TYPE_5__* tcps; } ;
typedef  TYPE_7__ opj_cp_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_18__ {int /*<<< orphan*/ * tccps; } ;
struct TYPE_13__ {int numcomps; } ;
struct TYPE_12__ {TYPE_1__* tile; void* main_head_end; } ;
struct TYPE_11__ {int tileno; int num_tps; TYPE_4__* tp; void* end_pos; void* start_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  J2K_STATE_TPH ; 
 int cio_getbp (int /*<<< orphan*/ *) ; 
 int cio_numbytesleft (int /*<<< orphan*/ *) ; 
 int cio_read (int /*<<< orphan*/ *,int) ; 
 void* cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,TYPE_9__*,int) ; 
 scalar_t__ opj_malloc (int) ; 

__attribute__((used)) static void j2k_read_sot(opj_j2k_t *j2k) {
	int len, tileno, totlen, partno, numparts, i;
	opj_tcp_t *tcp = NULL;
	char status = 0;

	opj_cp_t *cp = j2k->cp;
	opj_cio_t *cio = j2k->cio;

	len = cio_read(cio, 2);
	tileno = cio_read(cio, 2);

#ifdef USE_JPWL
	if (j2k->cp->correct) {

		static int backup_tileno = 0;

		/* tileno is negative or larger than the number of tiles!!! */
		if ((tileno < 0) || (tileno > (cp->tw * cp->th))) {
			opj_event_msg(j2k->cinfo, EVT_ERROR,
				"JPWL: bad tile number (%d out of a maximum of %d)\n",
				tileno, (cp->tw * cp->th));
			if (!JPWL_ASSUME) {
				opj_event_msg(j2k->cinfo, EVT_ERROR, "JPWL: giving up\n");
				return;
			}
			/* we try to correct */
			tileno = backup_tileno;
			opj_event_msg(j2k->cinfo, EVT_WARNING, "- trying to adjust this\n"
				"- setting tile number to %d\n",
				tileno);
		}

		/* keep your private count of tiles */
		backup_tileno++;
	};
#endif /* USE_JPWL */
	
	if (cp->tileno_size == 0) {
		cp->tileno[cp->tileno_size] = tileno;
		cp->tileno_size++;
	} else {
		i = 0;
		while (i < cp->tileno_size && status == 0) {
			status = cp->tileno[i] == tileno ? 1 : 0;
			i++;
		}
		if (status == 0) {
			cp->tileno[cp->tileno_size] = tileno;
			cp->tileno_size++;
		}
	}
	
	totlen = cio_read(cio, 4);

#ifdef USE_JPWL
	if (j2k->cp->correct) {

		/* totlen is negative or larger than the bytes left!!! */
		if ((totlen < 0) || (totlen > (cio_numbytesleft(cio) + 8))) {
			opj_event_msg(j2k->cinfo, EVT_ERROR,
				"JPWL: bad tile byte size (%d bytes against %d bytes left)\n",
				totlen, cio_numbytesleft(cio) + 8);
			if (!JPWL_ASSUME) {
				opj_event_msg(j2k->cinfo, EVT_ERROR, "JPWL: giving up\n");
				return;
			}
			/* we try to correct */
			totlen = 0;
			opj_event_msg(j2k->cinfo, EVT_WARNING, "- trying to adjust this\n"
				"- setting Psot to %d => assuming it is the last tile\n",
				totlen);
		}

	};
#endif /* USE_JPWL */

	if (!totlen)
		totlen = cio_numbytesleft(cio) + 8;
	
	partno = cio_read(cio, 1);
	numparts = cio_read(cio, 1);
	
	j2k->curtileno = tileno;
	j2k->cur_tp_num = partno;
	j2k->eot = cio_getbp(cio) - 12 + totlen;
	j2k->state = J2K_STATE_TPH;
	tcp = &cp->tcps[j2k->curtileno];

	/* Index */
	if (j2k->cstr_info) {
		if (tcp->first) {
			if (tileno == 0) 
				j2k->cstr_info->main_head_end = cio_tell(cio) - 13;
			j2k->cstr_info->tile[tileno].tileno = tileno;
			j2k->cstr_info->tile[tileno].start_pos = cio_tell(cio) - 12;
			j2k->cstr_info->tile[tileno].end_pos = j2k->cstr_info->tile[tileno].start_pos + totlen - 1;				
			j2k->cstr_info->tile[tileno].num_tps = numparts;
			if (numparts)
				j2k->cstr_info->tile[tileno].tp = (opj_tp_info_t *) opj_malloc(numparts * sizeof(opj_tp_info_t));
			else
				j2k->cstr_info->tile[tileno].tp = (opj_tp_info_t *) opj_malloc(10 * sizeof(opj_tp_info_t)); // Fixme (10)
		}
		else {
			j2k->cstr_info->tile[tileno].end_pos += totlen;
		}		
		j2k->cstr_info->tile[tileno].tp[partno].tp_start_pos = cio_tell(cio) - 12;
		j2k->cstr_info->tile[tileno].tp[partno].tp_end_pos = 
			j2k->cstr_info->tile[tileno].tp[partno].tp_start_pos + totlen - 1;
	}
	
	if (tcp->first == 1) {		
		/* Initialization PPT */
		opj_tccp_t *tmp = tcp->tccps;
		memcpy(tcp, j2k->default_tcp, sizeof(opj_tcp_t));
		tcp->ppt = 0;
		tcp->ppt_data = NULL;
		tcp->ppt_data_first = NULL;
		tcp->tccps = tmp;

		for (i = 0; i < j2k->image->numcomps; i++) {
			tcp->tccps[i] = j2k->default_tcp->tccps[i];
		}
		cp->tcps[j2k->curtileno].first = 0;
	}
}