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
 int /*<<< orphan*/ * allocate_job (int) ; 
 int /*<<< orphan*/  assertf (int,char*) ; 
 int /*<<< orphan*/  default_tube ; 
 int get_all_jobs_used () ; 
 int /*<<< orphan*/  job_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_job (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_tube (char*) ; 

void
cttest_job_all_jobs_used()
{
    Job *j, *x;

    TUBE_ASSIGN(default_tube, make_tube("default"));
    j = make_job(0, 0, 1, 0, default_tube);
    assertf(get_all_jobs_used() == 1, "should match");

    x = allocate_job(10);
    assertf(get_all_jobs_used() == 1, "should match");

    job_free(x);
    assertf(get_all_jobs_used() == 1, "should match");

    job_free(j);
    assertf(get_all_jobs_used() == 0, "should match");
}