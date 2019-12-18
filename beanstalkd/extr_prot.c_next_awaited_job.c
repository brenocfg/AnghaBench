#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_6__ {int /*<<< orphan*/ ** data; scalar_t__ len; } ;
struct TYPE_5__ {scalar_t__ len; } ;
struct TYPE_7__ {scalar_t__ unpause_at; TYPE_2__ ready; TYPE_1__ waiting_conns; scalar_t__ pause; } ;
typedef  TYPE_3__ Tube ;
struct TYPE_8__ {size_t len; TYPE_3__** items; } ;
typedef  int /*<<< orphan*/  Job ;

/* Variables and functions */
 scalar_t__ job_pri_less (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__ tubes ; 

__attribute__((used)) static Job *
next_awaited_job(int64 now)
{
    size_t i;
    Job *j = NULL;

    for (i = 0; i < tubes.len; i++) {
        Tube *t = tubes.items[i];
        if (t->pause) {
            if (t->unpause_at > now)
                continue;
            t->pause = 0;
        }
        if (t->waiting_conns.len && t->ready.len) {
            Job *candidate = t->ready.data[0];
            if (!j || job_pri_less(candidate, j)) {
                j = candidate;
            }
        }
    }
    return j;
}