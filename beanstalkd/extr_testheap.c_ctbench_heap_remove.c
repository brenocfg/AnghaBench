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
struct TYPE_4__ {int /*<<< orphan*/ ** data; int /*<<< orphan*/  setpos; int /*<<< orphan*/  less; } ;
typedef  int /*<<< orphan*/  Job ;
typedef  TYPE_1__ Heap ;

/* Variables and functions */
 int /*<<< orphan*/  assertf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ ** calloc (int,int) ; 
 int /*<<< orphan*/  ctresettimer () ; 
 int /*<<< orphan*/  ctstoptimer () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  heapinsert (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ heapremove (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  job_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  job_pri_less ; 
 int /*<<< orphan*/  job_setpos ; 
 int /*<<< orphan*/ * make_job (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ctbench_heap_remove(int n)
{
    Heap h = {
        .less = job_pri_less,
        .setpos = job_setpos,
    };
    int i;
    for (i = 0; i < n; i++) {
        Job *j = make_job(1, 0, 1, 0, 0);
        assertf(j, "allocate job");
        heapinsert(&h, j);
    }
    Job **jj = calloc(n, sizeof(Job *)); // temp storage to deallocate jobs later

    ctresettimer();
    for (i = 0; i < n; i++) {
        jj[i] = (Job *)heapremove(&h, 0);
    }
    ctstoptimer();

    free(h.data);
    for (i = 0; i < n; i++)
        job_free(jj[i]);
    free(jj);
}