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
typedef  scalar_t__ mstime_t ;
struct TYPE_4__ {scalar_t__ retry; scalar_t__ qtime; } ;
typedef  TYPE_1__ job ;

/* Variables and functions */
 int /*<<< orphan*/  updateJobAwakeTime (TYPE_1__*,int /*<<< orphan*/ ) ; 

void updateJobRequeueTime(job *j, mstime_t qtime) {
    /* Don't violate at-most-once (retry == 0) contract in case of bugs. */
    if (j->retry == 0 || j->qtime == 0) return;
    j->qtime = qtime;
    updateJobAwakeTime(j,0);
}