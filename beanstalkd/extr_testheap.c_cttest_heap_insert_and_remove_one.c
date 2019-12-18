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
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/  data; int /*<<< orphan*/  setpos; int /*<<< orphan*/  less; } ;
typedef  int /*<<< orphan*/  Job ;
typedef  TYPE_1__ Heap ;

/* Variables and functions */
 int /*<<< orphan*/  assertf (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int heapinsert (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heapremove (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  job_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  job_pri_less ; 
 int /*<<< orphan*/  job_setpos ; 
 int /*<<< orphan*/ * make_job (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
cttest_heap_insert_and_remove_one()
{
    Heap h = {
        .less = job_pri_less,
        .setpos = job_setpos,
    };

    Job *j1 = make_job(1, 0, 1, 0, 0);
    assertf(j1, "allocate job");

    int r = heapinsert(&h, j1);
    assertf(r, "insert should succeed");

    Job *got = heapremove(&h, 0);
    assertf(got == j1, "j1 should come back out");
    assertf(h.len == 0, "h should be empty.");

    free(h.data);
    job_free(j1);
}