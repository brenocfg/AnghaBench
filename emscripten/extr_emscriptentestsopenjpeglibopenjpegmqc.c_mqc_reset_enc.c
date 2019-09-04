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
 int /*<<< orphan*/  T1_CTXNO_AGG ; 
 int /*<<< orphan*/  T1_CTXNO_UNI ; 
 int /*<<< orphan*/  T1_CTXNO_ZC ; 
 int /*<<< orphan*/  mqc_resetstates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mqc_setstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void mqc_reset_enc(opj_mqc_t *mqc) {
	mqc_resetstates(mqc);
	mqc_setstate(mqc, T1_CTXNO_UNI, 0, 46);
	mqc_setstate(mqc, T1_CTXNO_AGG, 0, 3);
	mqc_setstate(mqc, T1_CTXNO_ZC, 0, 4);
}