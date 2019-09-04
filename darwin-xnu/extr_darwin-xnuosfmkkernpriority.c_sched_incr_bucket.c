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
typedef  size_t sched_bucket_t ;

/* Variables and functions */
 size_t TH_BUCKET_FIXPRI ; 
 size_t TH_BUCKET_SHARE_BG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  hw_atomic_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sched_run_buckets ; 

__attribute__((used)) static void
sched_incr_bucket(sched_bucket_t bucket)
{
	assert(bucket >= TH_BUCKET_FIXPRI &&
	       bucket <= TH_BUCKET_SHARE_BG);

	hw_atomic_add(&sched_run_buckets[bucket], 1);
}