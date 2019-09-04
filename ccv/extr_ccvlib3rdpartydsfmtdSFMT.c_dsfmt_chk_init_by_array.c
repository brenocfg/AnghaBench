#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  idx; TYPE_3__* status; } ;
typedef  TYPE_1__ dsfmt_t ;
struct TYPE_7__ {int* u32; } ;

/* Variables and functions */
 int DSFMT_N ; 
 int /*<<< orphan*/  DSFMT_N64 ; 
 int dsfmt_mexp ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 size_t idxof (int) ; 
 int ini_func1 (int) ; 
 int ini_func2 (int) ; 
 int /*<<< orphan*/  initial_mask (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  period_certification (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 

void dsfmt_chk_init_by_array(dsfmt_t *dsfmt, uint32_t init_key[],
			     int key_length, int mexp) {
    int i, j, count;
    uint32_t r;
    uint32_t *psfmt32;
    int lag;
    int mid;
    int size = (DSFMT_N + 1) * 4;	/* pulmonary */

    /* make sure caller program is compiled with the same MEXP */
    if (mexp != dsfmt_mexp) {
	fprintf(stderr, "DSFMT_MEXP doesn't match with dSFMT.c\n");
	exit(1);
    }
    if (size >= 623) {
	lag = 11;
    } else if (size >= 68) {
	lag = 7;
    } else if (size >= 39) {
	lag = 5;
    } else {
	lag = 3;
    }
    mid = (size - lag) / 2;

    psfmt32 = &dsfmt->status[0].u32[0];
    memset(dsfmt->status, 0x8b, sizeof(dsfmt->status));
    if (key_length + 1 > size) {
	count = key_length + 1;
    } else {
	count = size;
    }
    r = ini_func1(psfmt32[idxof(0)] ^ psfmt32[idxof(mid % size)]
		  ^ psfmt32[idxof((size - 1) % size)]);
    psfmt32[idxof(mid % size)] += r;
    r += key_length;
    psfmt32[idxof((mid + lag) % size)] += r;
    psfmt32[idxof(0)] = r;
    count--;
    for (i = 1, j = 0; (j < count) && (j < key_length); j++) {
	r = ini_func1(psfmt32[idxof(i)]
		      ^ psfmt32[idxof((i + mid) % size)]
		      ^ psfmt32[idxof((i + size - 1) % size)]);
	psfmt32[idxof((i + mid) % size)] += r;
	r += init_key[j] + i;
	psfmt32[idxof((i + mid + lag) % size)] += r;
	psfmt32[idxof(i)] = r;
	i = (i + 1) % size;
    }
    for (; j < count; j++) {
	r = ini_func1(psfmt32[idxof(i)]
		      ^ psfmt32[idxof((i + mid) % size)]
		      ^ psfmt32[idxof((i + size - 1) % size)]);
	psfmt32[idxof((i + mid) % size)] += r;
	r += i;
	psfmt32[idxof((i + mid + lag) % size)] += r;
	psfmt32[idxof(i)] = r;
	i = (i + 1) % size;
    }
    for (j = 0; j < size; j++) {
	r = ini_func2(psfmt32[idxof(i)]
		      + psfmt32[idxof((i + mid) % size)]
		      + psfmt32[idxof((i + size - 1) % size)]);
	psfmt32[idxof((i + mid) % size)] ^= r;
	r -= i;
	psfmt32[idxof((i + mid + lag) % size)] ^= r;
	psfmt32[idxof(i)] = r;
	i = (i + 1) % size;
    }
    initial_mask(dsfmt);
    period_certification(dsfmt);
    dsfmt->idx = DSFMT_N64;
}