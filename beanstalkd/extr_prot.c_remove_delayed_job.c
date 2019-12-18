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
struct TYPE_6__ {scalar_t__ state; } ;
struct TYPE_8__ {int /*<<< orphan*/  heap_index; TYPE_2__* tube; TYPE_1__ r; } ;
struct TYPE_7__ {int /*<<< orphan*/  delay; } ;
typedef  TYPE_3__ Job ;

/* Variables and functions */
 scalar_t__ Delayed ; 
 int /*<<< orphan*/  heapremove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Job *
remove_delayed_job(Job *j)
{
    if (!j || j->r.state != Delayed)
        return NULL;
    heapremove(&j->tube->delay, j->heap_index);

    return j;
}