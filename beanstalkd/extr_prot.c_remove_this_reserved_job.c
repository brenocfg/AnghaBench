#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * soonest_job; } ;
struct TYPE_14__ {int /*<<< orphan*/ * reserver; TYPE_2__* tube; } ;
struct TYPE_12__ {int /*<<< orphan*/  reserved_ct; } ;
struct TYPE_13__ {TYPE_1__ stat; } ;
struct TYPE_11__ {int /*<<< orphan*/  reserved_ct; } ;
typedef  TYPE_3__ Job ;
typedef  TYPE_4__ Conn ;

/* Variables and functions */
 TYPE_10__ global_stat ; 
 TYPE_3__* job_list_remove (TYPE_3__*) ; 

__attribute__((used)) static Job *
remove_this_reserved_job(Conn *c, Job *j)
{
    j = job_list_remove(j);
    if (j) {
        global_stat.reserved_ct--;
        j->tube->stat.reserved_ct--;
        j->reserver = NULL;
    }
    c->soonest_job = NULL;
    return j;
}