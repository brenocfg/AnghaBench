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
struct TYPE_7__ {int pdx; int pdy; int pw; scalar_t__ ph; } ;
typedef  TYPE_2__ opj_pi_resolution_t ;
struct TYPE_6__ {scalar_t__ ty0; scalar_t__ tx0; scalar_t__ ty1; scalar_t__ tx1; size_t compno0; size_t compno1; int resno0; int resno1; long layno0; long layno1; } ;
struct TYPE_8__ {size_t compno; int dx; int dy; int numcomps; scalar_t__ ty0; scalar_t__ tx0; scalar_t__ ty1; scalar_t__ tx1; int y; int x; int resno; int precno; long layno; long step_l; long step_r; long step_c; long step_p; int* include; TYPE_1__ poc; TYPE_4__* comps; int /*<<< orphan*/  tp_on; scalar_t__ first; } ;
typedef  TYPE_3__ opj_pi_iterator_t ;
struct TYPE_9__ {int numresolutions; int dx; int dy; TYPE_2__* resolutions; } ;
typedef  TYPE_4__ opj_pi_comp_t ;

/* Variables and functions */
 int int_ceildiv (scalar_t__,int) ; 
 int int_floordivpow2 (int,int) ; 
 int int_min (int,int) ; 

__attribute__((used)) static bool pi_next_pcrl(opj_pi_iterator_t * pi) {
	opj_pi_comp_t *comp = NULL;
	opj_pi_resolution_t *res = NULL;
	long index = 0;

	if (!pi->first) {
		comp = &pi->comps[pi->compno];
		goto LABEL_SKIP;
	} else {
		int compno, resno;
		pi->first = 0;
		pi->dx = 0;
		pi->dy = 0;
		for (compno = 0; compno < pi->numcomps; compno++) {
			comp = &pi->comps[compno];
			for (resno = 0; resno < comp->numresolutions; resno++) {
				int dx, dy;
				res = &comp->resolutions[resno];
				dx = comp->dx * (1 << (res->pdx + comp->numresolutions - 1 - resno));
				dy = comp->dy * (1 << (res->pdy + comp->numresolutions - 1 - resno));
				pi->dx = !pi->dx ? dx : int_min(pi->dx, dx);
				pi->dy = !pi->dy ? dy : int_min(pi->dy, dy);
			}
		}
	}
	if (!pi->tp_on){
			pi->poc.ty0 = pi->ty0;
			pi->poc.tx0 = pi->tx0;
			pi->poc.ty1 = pi->ty1;
			pi->poc.tx1 = pi->tx1;
		}
	for (pi->y = pi->poc.ty0; pi->y < pi->poc.ty1; pi->y += pi->dy - (pi->y % pi->dy)) {
		for (pi->x = pi->poc.tx0; pi->x < pi->poc.tx1; pi->x += pi->dx - (pi->x % pi->dx)) {
			for (pi->compno = pi->poc.compno0; pi->compno < pi->poc.compno1; pi->compno++) {
				comp = &pi->comps[pi->compno];
				for (pi->resno = pi->poc.resno0; pi->resno < int_min(pi->poc.resno1, comp->numresolutions); pi->resno++) {
					int levelno;
					int trx0, try0;
					int trx1, try1;
					int rpx, rpy;
					int prci, prcj;
					res = &comp->resolutions[pi->resno];
					levelno = comp->numresolutions - 1 - pi->resno;
					trx0 = int_ceildiv(pi->tx0, comp->dx << levelno);
					try0 = int_ceildiv(pi->ty0, comp->dy << levelno);
					trx1 = int_ceildiv(pi->tx1, comp->dx << levelno);
					try1 = int_ceildiv(pi->ty1, comp->dy << levelno);
					rpx = res->pdx + levelno;
					rpy = res->pdy + levelno;
					if (!((pi->y % (comp->dy << rpy) == 0) || ((pi->y == pi->ty0) && ((try0 << levelno) % (1 << rpy))))){
						continue;	
					}
					if (!((pi->x % (comp->dx << rpx) == 0) || ((pi->x == pi->tx0) && ((trx0 << levelno) % (1 << rpx))))){
						continue; 
					}
					
					if ((res->pw==0)||(res->ph==0)) continue;
					
					if ((trx0==trx1)||(try0==try1)) continue;
					
					prci = int_floordivpow2(int_ceildiv(pi->x, comp->dx << levelno), res->pdx) 
						 - int_floordivpow2(trx0, res->pdx);
					prcj = int_floordivpow2(int_ceildiv(pi->y, comp->dy << levelno), res->pdy) 
						 - int_floordivpow2(try0, res->pdy);
					pi->precno = prci + prcj * res->pw;
					for (pi->layno = pi->poc.layno0; pi->layno < pi->poc.layno1; pi->layno++) {
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
	}
	
	return false;
}