#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int id; } ;
struct TYPE_7__ {TYPE_1__ r; } ;
typedef  TYPE_2__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  TUBE_ASSIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  default_tube ; 
 int /*<<< orphan*/  job_pri_less (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* make_job (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_tube (char*) ; 

void
cttest_job_cmp_ids()
{
    Job *a, *b;

    TUBE_ASSIGN(default_tube, make_tube("default"));
    a = make_job(1, 0, 1, 0, default_tube);
    b = make_job(1, 0, 1, 0, default_tube);

    b->r.id <<= 49;
    assertf(job_pri_less(a, b), "should be less");
}