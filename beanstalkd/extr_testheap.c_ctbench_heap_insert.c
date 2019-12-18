#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__** data; int /*<<< orphan*/  setpos; int /*<<< orphan*/  less; } ;
struct TYPE_11__ {int /*<<< orphan*/  id; int /*<<< orphan*/  pri; } ;
struct TYPE_12__ {TYPE_1__ r; } ;
typedef  TYPE_2__ Job ;
typedef  TYPE_3__ Heap ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 TYPE_2__** calloc (int,int) ; 
 int /*<<< orphan*/  ctresettimer () ; 
 int /*<<< orphan*/  ctstoptimer () ; 
 int /*<<< orphan*/  free (TYPE_2__**) ; 
 int /*<<< orphan*/  heapinsert (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  heapremove (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  job_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  job_pri_less ; 
 int /*<<< orphan*/  job_setpos ; 
 TYPE_2__* make_job (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ctbench_heap_insert(int n)
{
    Job **j = calloc(n, sizeof *j);
    int i;
    for (i = 0; i < n; i++) {
        j[i] = make_job(1, 0, 1, 0, 0);
        assert(j[i]);
        j[i]->r.pri = -j[i]->r.id;
    }
    Heap h = {
        .less = job_pri_less,
        .setpos = job_setpos,
    };

    ctresettimer();
    for (i = 0; i < n; i++) {
        heapinsert(&h, j[i]);
    }
    ctstoptimer();

    for (i = 0; i < n; i++)
        job_free(heapremove(&h, 0));
    free(h.data);
    free(j);
}