#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Job ;

/* Variables and functions */
 int /*<<< orphan*/  TUBE_ASSIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  default_tube ; 
 int /*<<< orphan*/  job_pri_less (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_job (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_tube (char*) ; 

void
cttest_job_cmp_pris()
{
    Job *a, *b;

    TUBE_ASSIGN(default_tube, make_tube("default"));
    a = make_job(1, 0, 1, 0, default_tube);
    b = make_job(1 << 27, 0, 1, 0, default_tube);

    assertf(job_pri_less(a, b), "should be less");
}