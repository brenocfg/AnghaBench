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
typedef  TYPE_1__* workq_threadreq_t ;
struct uthread {int /*<<< orphan*/  uu_workq_pri; } ;
struct TYPE_4__ {scalar_t__ tr_qos; } ;

/* Variables and functions */
 scalar_t__ workq_pri_override (int /*<<< orphan*/ ) ; 
 scalar_t__ workq_thread_needs_params_change (TYPE_1__*,struct uthread*) ; 

__attribute__((used)) static inline bool
workq_thread_needs_priority_change(workq_threadreq_t req, struct uthread *uth)
{
	if (workq_thread_needs_params_change(req, uth)) {
		return true;
	}

	return req->tr_qos != workq_pri_override(uth->uu_workq_pri);
}