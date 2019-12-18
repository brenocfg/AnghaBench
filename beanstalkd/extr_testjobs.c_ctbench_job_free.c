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
 int /*<<< orphan*/ ** calloc (int,int) ; 
 int /*<<< orphan*/  ctresettimer () ; 
 int /*<<< orphan*/  ctstoptimer () ; 
 int /*<<< orphan*/  default_tube ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  job_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_job (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_tube (char*) ; 

void
ctbench_job_free(int n)
{
    int i;
    Job **j = calloc(n, sizeof *j);
    TUBE_ASSIGN(default_tube, make_tube("default"));
    for (i = 0; i < n; i++) {
        j[i] = make_job(0, 0, 1, 0, default_tube);
    }

    ctresettimer();
    for (i = 0; i < n; i++) {
        job_free(j[i]);
    }
    ctstoptimer();

    free(j);
}