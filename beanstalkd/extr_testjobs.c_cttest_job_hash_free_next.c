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
typedef  int uint64 ;
struct TYPE_4__ {struct TYPE_4__* ht_next; } ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  TUBE_ASSIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertf (int,char*) ; 
 int /*<<< orphan*/  default_tube ; 
 int /*<<< orphan*/  job_free (TYPE_1__*) ; 
 TYPE_1__* make_job_with_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  make_tube (char*) ; 

void
cttest_job_hash_free_next()
{
    Job *a, *b;
    uint64 aid = 97, bid = 12386;

    TUBE_ASSIGN(default_tube, make_tube("default"));
    b = make_job_with_id(0, 0, 1, 0, default_tube, bid);
    a = make_job_with_id(0, 0, 1, 0, default_tube, aid);

    assertf(a->ht_next == b, "b should be chained to a");

    job_free(b);

    assertf(a->ht_next == NULL, "job should be missing");
}