#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* workq_threadreq_t ;
struct TYPE_11__ {int trp_flags; scalar_t__ trp_pri; scalar_t__ trp_pol; int /*<<< orphan*/  trp_value; } ;
typedef  TYPE_4__ workq_threadreq_param_t ;
typedef  int uint16_t ;
struct TYPE_8__ {int /*<<< orphan*/  workloop_params; } ;
struct TYPE_9__ {TYPE_1__ uus_workq_park_data; } ;
struct uthread {TYPE_2__ uu_save; } ;
struct TYPE_10__ {int tr_flags; } ;

/* Variables and functions */
 int TRP_CPUPERCENT ; 
 int TRP_POLICY ; 
 int TRP_PRIORITY ; 
 int TR_FLAG_WL_PARAMS ; 
 TYPE_4__ kqueue_threadreq_workloop_param (TYPE_3__*) ; 

__attribute__((used)) static inline bool
workq_thread_needs_params_change(workq_threadreq_t req, struct uthread *uth)
{
	workq_threadreq_param_t cur_trp, req_trp = { };

	cur_trp.trp_value = uth->uu_save.uus_workq_park_data.workloop_params;
	if (req->tr_flags & TR_FLAG_WL_PARAMS) {
		req_trp = kqueue_threadreq_workloop_param(req);
	}

	/*
	 * CPU percent flags are handled separately to policy changes, so ignore
	 * them for all of these checks.
	 */
	uint16_t cur_flags = (cur_trp.trp_flags & ~TRP_CPUPERCENT);
	uint16_t req_flags = (req_trp.trp_flags & ~TRP_CPUPERCENT);

	if (!req_flags && !cur_flags) {
		return false;
	}

	if (req_flags != cur_flags) {
		return true;
	}

	if ((req_flags & TRP_PRIORITY) && req_trp.trp_pri != cur_trp.trp_pri) {
		return true;
	}

	if ((req_flags & TRP_POLICY) && cur_trp.trp_pol != cur_trp.trp_pol) {
		return true;
	}

	return false;
}