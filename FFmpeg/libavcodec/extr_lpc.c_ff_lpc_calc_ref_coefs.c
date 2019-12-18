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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  blocksize; int /*<<< orphan*/  windowed_samples; int /*<<< orphan*/  (* lpc_compute_autocorr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,double*) ;int /*<<< orphan*/  (* lpc_apply_welch_window ) (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ LPCContext ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_LPC_ORDER ; 
 int /*<<< orphan*/  compute_ref_coefs (double*,int,double*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,double*) ; 

int ff_lpc_calc_ref_coefs(LPCContext *s,
                          const int32_t *samples, int order, double *ref)
{
    double autoc[MAX_LPC_ORDER + 1];

    s->lpc_apply_welch_window(samples, s->blocksize, s->windowed_samples);
    s->lpc_compute_autocorr(s->windowed_samples, s->blocksize, order, autoc);
    compute_ref_coefs(autoc, order, ref, NULL);

    return order;
}