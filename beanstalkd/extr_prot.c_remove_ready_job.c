#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  urgent_ct; } ;
struct TYPE_8__ {scalar_t__ state; scalar_t__ pri; } ;
struct TYPE_11__ {TYPE_2__* tube; TYPE_1__ r; int /*<<< orphan*/  heap_index; } ;
struct TYPE_10__ {int /*<<< orphan*/  urgent_ct; } ;
struct TYPE_9__ {TYPE_3__ stat; int /*<<< orphan*/  ready; } ;
typedef  TYPE_4__ Job ;

/* Variables and functions */
 scalar_t__ Ready ; 
 scalar_t__ URGENT_THRESHOLD ; 
 TYPE_7__ global_stat ; 
 int /*<<< orphan*/  heapremove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ready_ct ; 

__attribute__((used)) static Job *
remove_ready_job(Job *j)
{
    if (!j || j->r.state != Ready)
        return NULL;
    heapremove(&j->tube->ready, j->heap_index);
    ready_ct--;
    if (j->r.pri < URGENT_THRESHOLD) {
        global_stat.urgent_ct--;
        j->tube->stat.urgent_ct--;
    }
    return j;
}