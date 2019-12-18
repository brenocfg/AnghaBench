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
struct request {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_rq_merge_ok (struct request*,struct bio*) ; 
 int /*<<< orphan*/  elv_iosched_allow_merge (struct request*,struct bio*) ; 

bool elv_rq_merge_ok(struct request *rq, struct bio *bio)
{
	if (!blk_rq_merge_ok(rq, bio))
		return 0;

	if (!elv_iosched_allow_merge(rq, bio))
		return 0;

	return 1;
}