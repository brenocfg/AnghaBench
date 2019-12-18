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

/* Variables and functions */
 int /*<<< orphan*/  TUBE_ASSIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertf (int,char*) ; 
 int /*<<< orphan*/  default_tube ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int get_all_jobs_used () ; 
 int /*<<< orphan*/  job_find (int) ; 
 int /*<<< orphan*/  job_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_job (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_tube (char*) ; 
 int /*<<< orphan*/  stderr ; 

void
cttest_job_100_000_jobs()
{
    int i;

    TUBE_ASSIGN(default_tube, make_tube("default"));
    for (i = 0; i < 100000; i++) {
        make_job(0, 0, 1, 0, default_tube);
    }
    assertf(get_all_jobs_used() == 100000, "should match");

    for (i = 1; i <= 100000; i++) {
        job_free(job_find(i));
    }
    fprintf(stderr, "get_all_jobs_used() => %zu\n", get_all_jobs_used());
    assertf(get_all_jobs_used() == 0, "should match");
}