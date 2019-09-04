#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* cp; } ;
typedef  TYPE_1__ opj_j2k_t ;
struct TYPE_7__ {int /*<<< orphan*/  cp_limit_decoding; int /*<<< orphan*/  cp_layer; int /*<<< orphan*/  cp_reduce; } ;
typedef  TYPE_2__ opj_dparameters_t ;
struct TYPE_8__ {int /*<<< orphan*/  limit_decoding; int /*<<< orphan*/  layer; int /*<<< orphan*/  reduce; } ;
typedef  TYPE_3__ opj_cp_t ;

/* Variables and functions */
 scalar_t__ opj_calloc (int,int) ; 

void j2k_setup_decoder(opj_j2k_t *j2k, opj_dparameters_t *parameters) {
	if(j2k && parameters) {
		/* create and initialize the coding parameters structure */
		opj_cp_t *cp = (opj_cp_t*) opj_calloc(1, sizeof(opj_cp_t));
		cp->reduce = parameters->cp_reduce;	
		cp->layer = parameters->cp_layer;
		cp->limit_decoding = parameters->cp_limit_decoding;

#ifdef USE_JPWL
		cp->correct = parameters->jpwl_correct;
		cp->exp_comps = parameters->jpwl_exp_comps;
		cp->max_tiles = parameters->jpwl_max_tiles;
#endif /* USE_JPWL */


		/* keep a link to cp so that we can destroy it later in j2k_destroy_decompress */
		j2k->cp = cp;
	}
}