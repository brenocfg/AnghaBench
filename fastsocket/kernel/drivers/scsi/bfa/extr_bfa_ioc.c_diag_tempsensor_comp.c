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
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ lock; scalar_t__ status; int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cbfn ) (int /*<<< orphan*/ ,scalar_t__) ;TYPE_1__* temp; } ;
struct bfa_diag_s {TYPE_2__ tsensor; } ;
struct TYPE_7__ {scalar_t__ temp; scalar_t__ ts_junc; scalar_t__ ts_brd; scalar_t__ status; scalar_t__ brd_temp; } ;
typedef  TYPE_3__ bfi_diag_ts_rsp_t ;
struct TYPE_5__ {scalar_t__ ts_junc; scalar_t__ ts_brd; scalar_t__ status; void* brd_temp; void* temp; } ;

/* Variables and functions */
 scalar_t__ BFA_STATUS_OK ; 
 void* be16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_diag_s*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
diag_tempsensor_comp(struct bfa_diag_s *diag, bfi_diag_ts_rsp_t *rsp)
{
	if (!diag->tsensor.lock) {
		/* receiving response after ioc failure */
		bfa_trc(diag, diag->tsensor.lock);
		return;
	}

	/*
	 * ASIC junction tempsensor is a reg read operation
	 * it will always return OK
	 */
	diag->tsensor.temp->temp = be16_to_cpu(rsp->temp);
	diag->tsensor.temp->ts_junc = rsp->ts_junc;
	diag->tsensor.temp->ts_brd = rsp->ts_brd;

	if (rsp->ts_brd) {
		/* tsensor.temp->status is brd_temp status */
		diag->tsensor.temp->status = rsp->status;
		if (rsp->status == BFA_STATUS_OK) {
			diag->tsensor.temp->brd_temp =
				be16_to_cpu(rsp->brd_temp);
		} else
			diag->tsensor.temp->brd_temp = 0;
	}

	bfa_trc(diag, rsp->status);
	bfa_trc(diag, rsp->ts_junc);
	bfa_trc(diag, rsp->temp);
	bfa_trc(diag, rsp->ts_brd);
	bfa_trc(diag, rsp->brd_temp);

	/* tsensor status is always good bcos we always have junction temp */
	diag->tsensor.status = BFA_STATUS_OK;
	diag->tsensor.cbfn(diag->tsensor.cbarg, diag->tsensor.status);
	diag->tsensor.lock = 0;
}