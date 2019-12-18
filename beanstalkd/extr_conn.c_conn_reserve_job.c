#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int pending_timeout; int /*<<< orphan*/  reserved_jobs; } ;
struct TYPE_13__ {int /*<<< orphan*/  state; scalar_t__ ttr; scalar_t__ deadline_at; int /*<<< orphan*/  reserve_ct; } ;
struct TYPE_14__ {TYPE_5__* reserver; TYPE_3__ r; TYPE_2__* tube; } ;
struct TYPE_11__ {int /*<<< orphan*/  reserved_ct; } ;
struct TYPE_12__ {TYPE_1__ stat; } ;
typedef  TYPE_4__ Job ;
typedef  TYPE_5__ Conn ;

/* Variables and functions */
 int /*<<< orphan*/  Reserved ; 
 int /*<<< orphan*/  conn_set_soonestjob (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  job_list_insert (int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ nanoseconds () ; 

void
conn_reserve_job(Conn *c, Job *j) {
    j->tube->stat.reserved_ct++;
    j->r.reserve_ct++;

    j->r.deadline_at = nanoseconds() + j->r.ttr;
    j->r.state = Reserved;
    job_list_insert(&c->reserved_jobs, j);
    j->reserver = c;
    c->pending_timeout = -1;
    conn_set_soonestjob(c, j);
}