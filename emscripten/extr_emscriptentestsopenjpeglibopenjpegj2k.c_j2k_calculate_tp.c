#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_tp_info_t ;
struct TYPE_13__ {int numpocs; } ;
typedef  TYPE_3__ opj_tcp_t ;
typedef  int /*<<< orphan*/  opj_pi_iterator_t ;
struct TYPE_14__ {int* cur_totnum_tp; TYPE_2__* cstr_info; } ;
typedef  TYPE_4__ opj_j2k_t ;
typedef  int /*<<< orphan*/  opj_image_t ;
struct TYPE_15__ {int tw; int th; TYPE_3__* tcps; } ;
typedef  TYPE_5__ opj_cp_t ;
struct TYPE_12__ {TYPE_1__* tile; } ;
struct TYPE_11__ {int num_tps; int /*<<< orphan*/ * tp; } ;

/* Variables and functions */
 int /*<<< orphan*/  FINAL_PASS ; 
 int j2k_get_num_tp (TYPE_5__*,int,int) ; 
 scalar_t__ opj_malloc (int) ; 
 int /*<<< orphan*/  pi_destroy (int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 int /*<<< orphan*/ * pi_initialise_encode (int /*<<< orphan*/ *,TYPE_5__*,int,int /*<<< orphan*/ ) ; 

int j2k_calculate_tp(opj_cp_t *cp,int img_numcomp,opj_image_t *image,opj_j2k_t *j2k ){
	int pino,tileno,totnum_tp=0;
	j2k->cur_totnum_tp = (int *) opj_malloc(cp->tw * cp->th * sizeof(int));
	for (tileno = 0; tileno < cp->tw * cp->th; tileno++) {
		int cur_totnum_tp = 0;
		opj_tcp_t *tcp = &cp->tcps[tileno];
		for(pino = 0; pino <= tcp->numpocs; pino++) {
			int tp_num=0;
			opj_pi_iterator_t *pi = pi_initialise_encode(image, cp, tileno,FINAL_PASS);
			if(!pi) { return -1;}
			tp_num = j2k_get_num_tp(cp,pino,tileno);
			totnum_tp = totnum_tp + tp_num;
			cur_totnum_tp = cur_totnum_tp + tp_num;
			pi_destroy(pi, cp, tileno);
		}
		j2k->cur_totnum_tp[tileno] = cur_totnum_tp;
		/* INDEX >> */
		if (j2k->cstr_info) {
			j2k->cstr_info->tile[tileno].num_tps = cur_totnum_tp;
			j2k->cstr_info->tile[tileno].tp = (opj_tp_info_t *) opj_malloc(cur_totnum_tp * sizeof(opj_tp_info_t));
		}
		/* << INDEX */
	}
	return totnum_tp;
}