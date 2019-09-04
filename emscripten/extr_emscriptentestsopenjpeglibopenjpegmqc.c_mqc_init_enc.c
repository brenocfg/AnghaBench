#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int a; unsigned char* bp; int ct; unsigned char* start; scalar_t__ c; } ;
typedef  TYPE_1__ opj_mqc_t ;

/* Variables and functions */
 int /*<<< orphan*/  mqc_setcurctx (TYPE_1__*,int /*<<< orphan*/ ) ; 

void mqc_init_enc(opj_mqc_t *mqc, unsigned char *bp) {
	mqc_setcurctx(mqc, 0);
	mqc->a = 0x8000;
	mqc->c = 0;
	mqc->bp = bp - 1;
	mqc->ct = 12;
	if (*mqc->bp == 0xff) {
		mqc->ct = 13;
	}
	mqc->start = bp;
}