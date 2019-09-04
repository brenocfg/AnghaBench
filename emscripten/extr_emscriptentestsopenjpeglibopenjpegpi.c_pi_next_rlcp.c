#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int pw; int ph; } ;
typedef  TYPE_2__ opj_pi_resolution_t ;
struct TYPE_6__ {size_t resno0; size_t resno1; long layno0; long layno1; size_t compno0; size_t compno1; int precno1; long precno0; } ;
struct TYPE_8__ {size_t compno; size_t resno; long layno; long precno; long step_l; long step_r; long step_c; long step_p; int* include; TYPE_1__ poc; int /*<<< orphan*/  tp_on; TYPE_4__* comps; scalar_t__ first; } ;
typedef  TYPE_3__ opj_pi_iterator_t ;
struct TYPE_9__ {size_t numresolutions; TYPE_2__* resolutions; } ;
typedef  TYPE_4__ opj_pi_comp_t ;

/* Variables and functions */

__attribute__((used)) static bool pi_next_rlcp(opj_pi_iterator_t * pi) {
	opj_pi_comp_t *comp = NULL;
	opj_pi_resolution_t *res = NULL;
	long index = 0;

	if (!pi->first) {
		comp = &pi->comps[pi->compno];
		res = &comp->resolutions[pi->resno];
		goto LABEL_SKIP;
	} else {
		pi->first = 0;
	}

	for (pi->resno = pi->poc.resno0; pi->resno < pi->poc.resno1; pi->resno++) {
		for (pi->layno = pi->poc.layno0; pi->layno < pi->poc.layno1; pi->layno++) {
			for (pi->compno = pi->poc.compno0; pi->compno < pi->poc.compno1; pi->compno++) {
				comp = &pi->comps[pi->compno];
				if (pi->resno >= comp->numresolutions) {
					continue;
				}
				res = &comp->resolutions[pi->resno];
				if(!pi->tp_on){
					pi->poc.precno1 = res->pw * res->ph;
				}
				for (pi->precno = pi->poc.precno0; pi->precno < pi->poc.precno1; pi->precno++) {
					index = pi->layno * pi->step_l + pi->resno * pi->step_r + pi->compno * pi->step_c + pi->precno * pi->step_p;
					if (!pi->include[index]) {
						pi->include[index] = 1;
						return true;
					}
LABEL_SKIP:;
				}
			}
		}
	}
	
	return false;
}