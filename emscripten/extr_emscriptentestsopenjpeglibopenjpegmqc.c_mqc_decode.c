#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int a; int c; TYPE_1__** curctx; } ;
typedef  TYPE_2__ opj_mqc_t ;
struct TYPE_7__ {int qeval; int mps; } ;

/* Variables and functions */
 int mqc_lpsexchange (TYPE_2__* const) ; 
 int mqc_mpsexchange (TYPE_2__* const) ; 
 int /*<<< orphan*/  mqc_renormd (TYPE_2__* const) ; 

int mqc_decode(opj_mqc_t *const mqc) {
	int d;
	mqc->a -= (*mqc->curctx)->qeval;
	if ((mqc->c >> 16) < (*mqc->curctx)->qeval) {
		d = mqc_lpsexchange(mqc);
		mqc_renormd(mqc);
	} else {
		mqc->c -= (*mqc->curctx)->qeval << 16;
		if ((mqc->a & 0x8000) == 0) {
			d = mqc_mpsexchange(mqc);
			mqc_renormd(mqc);
		} else {
			d = (*mqc->curctx)->mps;
		}
	}

	return d;
}