#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dw128_t ;
struct TYPE_3__ {int /*<<< orphan*/ * status; } ;
typedef  TYPE_1__ dsfmt_t ;

/* Variables and functions */
 size_t DSFMT_N ; 
 size_t DSFMT_POS1 ; 
 int /*<<< orphan*/  do_recursion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void dsfmt_gen_rand_all(dsfmt_t *dsfmt) {
    int i;
    dw128_t lung;

    lung = dsfmt->status[DSFMT_N];
    do_recursion(&dsfmt->status[0], &dsfmt->status[0],
		 &dsfmt->status[DSFMT_POS1], &lung);
    for (i = 1; i < DSFMT_N - DSFMT_POS1; i++) {
	do_recursion(&dsfmt->status[i], &dsfmt->status[i],
		     &dsfmt->status[i + DSFMT_POS1], &lung);
    }
    for (; i < DSFMT_N; i++) {
	do_recursion(&dsfmt->status[i], &dsfmt->status[i],
		     &dsfmt->status[i + DSFMT_POS1 - DSFMT_N], &lung);
    }
    dsfmt->status[DSFMT_N] = lung;
}