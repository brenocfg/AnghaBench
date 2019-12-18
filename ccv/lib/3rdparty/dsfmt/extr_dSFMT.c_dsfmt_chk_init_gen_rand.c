#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  idx; TYPE_1__* status; } ;
typedef  TYPE_2__ dsfmt_t ;
struct TYPE_6__ {int* u32; } ;

/* Variables and functions */
 int DSFMT_N ; 
 int /*<<< orphan*/  DSFMT_N64 ; 
 int dsfmt_mexp ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 size_t idxof (int) ; 
 int /*<<< orphan*/  initial_mask (TYPE_2__*) ; 
 int /*<<< orphan*/  period_certification (TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 

void dsfmt_chk_init_gen_rand(dsfmt_t *dsfmt, uint32_t seed, int mexp) {
    int i;
    uint32_t *psfmt;

    /* make sure caller program is compiled with the same MEXP */
    if (mexp != dsfmt_mexp) {
	fprintf(stderr, "DSFMT_MEXP doesn't match with dSFMT.c\n");
	exit(1);
    }
    psfmt = &dsfmt->status[0].u32[0];
    psfmt[idxof(0)] = seed;
    for (i = 1; i < (DSFMT_N + 1) * 4; i++) {
        psfmt[idxof(i)] = 1812433253UL
	    * (psfmt[idxof(i - 1)] ^ (psfmt[idxof(i - 1)] >> 30)) + i;
    }
    initial_mask(dsfmt);
    period_certification(dsfmt);
    dsfmt->idx = DSFMT_N64;
}