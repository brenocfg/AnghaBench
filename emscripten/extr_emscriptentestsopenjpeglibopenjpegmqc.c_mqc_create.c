#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  opj_mqc_t ;

/* Variables and functions */
 scalar_t__ opj_malloc (int) ; 

opj_mqc_t* mqc_create(void) {
	opj_mqc_t *mqc = (opj_mqc_t*)opj_malloc(sizeof(opj_mqc_t));
#ifdef MQC_PERF_OPT
	mqc->buffer = NULL;
#endif
	return mqc;
}