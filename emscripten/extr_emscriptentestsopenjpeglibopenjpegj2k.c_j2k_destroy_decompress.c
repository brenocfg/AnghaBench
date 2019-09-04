#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int tw; int th; struct TYPE_6__* comment; struct TYPE_6__* tileno; struct TYPE_6__* ppm_data_first; struct TYPE_6__* tcps; struct TYPE_6__* tccps; struct TYPE_6__* ppt_data_first; struct TYPE_6__* cp; struct TYPE_6__* default_tcp; struct TYPE_6__* tile_data; struct TYPE_6__* tile_len; } ;
typedef  TYPE_1__ opj_tcp_t ;
typedef  TYPE_1__ opj_j2k_t ;
typedef  TYPE_1__ opj_cp_t ;

/* Variables and functions */
 int /*<<< orphan*/  opj_free (TYPE_1__*) ; 

void j2k_destroy_decompress(opj_j2k_t *j2k) {
	int i = 0;

	if(j2k->tile_len != NULL) {
		opj_free(j2k->tile_len);
	}
	if(j2k->tile_data != NULL) {
		opj_free(j2k->tile_data);
	}
	if(j2k->default_tcp != NULL) {
		opj_tcp_t *default_tcp = j2k->default_tcp;
		if(default_tcp->ppt_data_first != NULL) {
			opj_free(default_tcp->ppt_data_first);
		}
		if(j2k->default_tcp->tccps != NULL) {
			opj_free(j2k->default_tcp->tccps);
		}
		opj_free(j2k->default_tcp);
	}
	if(j2k->cp != NULL) {
		opj_cp_t *cp = j2k->cp;
		if(cp->tcps != NULL) {
			for(i = 0; i < cp->tw * cp->th; i++) {
				if(cp->tcps[i].ppt_data_first != NULL) {
					opj_free(cp->tcps[i].ppt_data_first);
				}
				if(cp->tcps[i].tccps != NULL) {
					opj_free(cp->tcps[i].tccps);
				}
			}
			opj_free(cp->tcps);
		}
		if(cp->ppm_data_first != NULL) {
			opj_free(cp->ppm_data_first);
		}
		if(cp->tileno != NULL) {
			opj_free(cp->tileno);  
		}
		if(cp->comment != NULL) {
			opj_free(cp->comment);
		}

		opj_free(cp);
	}
	opj_free(j2k);
}