#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * soonest_job; } ;
struct TYPE_8__ {scalar_t__ ttr; scalar_t__ deadline_at; } ;
struct TYPE_9__ {TYPE_1__ r; } ;
typedef  TYPE_2__ Job ;
typedef  TYPE_3__ Conn ;

/* Variables and functions */
 scalar_t__ is_job_reserved_by_conn (TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ nanoseconds () ; 

__attribute__((used)) static bool
touch_job(Conn *c, Job *j)
{
    if (is_job_reserved_by_conn(c, j)) {
        j->r.deadline_at = nanoseconds() + j->r.ttr;
        c->soonest_job = NULL;
        return true;
    }
    return false;
}