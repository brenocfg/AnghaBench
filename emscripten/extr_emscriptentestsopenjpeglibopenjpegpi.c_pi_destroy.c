#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int numpocs; } ;
typedef  TYPE_1__ opj_tcp_t ;
struct TYPE_9__ {int numcomps; struct TYPE_9__* include; struct TYPE_9__* comps; struct TYPE_9__* resolutions; } ;
typedef  TYPE_2__ opj_pi_iterator_t ;
typedef  TYPE_2__ opj_pi_comp_t ;
struct TYPE_10__ {TYPE_1__* tcps; } ;
typedef  TYPE_4__ opj_cp_t ;

/* Variables and functions */
 int /*<<< orphan*/  opj_free (TYPE_2__*) ; 

void pi_destroy(opj_pi_iterator_t *pi, opj_cp_t *cp, int tileno) {
	int compno, pino;
	opj_tcp_t *tcp = &cp->tcps[tileno];
	if(pi) {
		for (pino = 0; pino < tcp->numpocs + 1; pino++) {	
			if(pi[pino].comps) {
				for (compno = 0; compno < pi->numcomps; compno++) {
					opj_pi_comp_t *comp = &pi[pino].comps[compno];
					if(comp->resolutions) {
						opj_free(comp->resolutions);
					}
				}
				opj_free(pi[pino].comps);
			}
		}
		if(pi->include) {
			opj_free(pi->include);
		}
		opj_free(pi);
	}
}