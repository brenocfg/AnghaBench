#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* soonest_job; } ;
struct TYPE_6__ {scalar_t__ deadline_at; } ;
struct TYPE_7__ {TYPE_1__ r; } ;
typedef  TYPE_2__ Job ;
typedef  TYPE_3__ Conn ;

/* Variables and functions */

__attribute__((used)) static void
conn_set_soonestjob(Conn *c, Job *j) {
    if (!c->soonest_job || j->r.deadline_at < c->soonest_job->r.deadline_at) {
        c->soonest_job = j;
    }
}