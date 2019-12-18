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
typedef  int uint64 ;
typedef  int /*<<< orphan*/  Job ;

/* Variables and functions */
 int /*<<< orphan*/  TUBE_ASSIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertf (int,char*) ; 
 int /*<<< orphan*/  default_tube ; 
 int /*<<< orphan*/  job_find (int) ; 
 int /*<<< orphan*/  job_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_job_with_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  make_tube (char*) ; 

void
cttest_job_hash_free()
{
    Job *j;
    uint64 jid = 83;

    TUBE_ASSIGN(default_tube, make_tube("default"));
    j = make_job_with_id(0, 0, 1, 0, default_tube, jid);
    job_free(j);

    assertf(!job_find(jid), "job should be missing");
}