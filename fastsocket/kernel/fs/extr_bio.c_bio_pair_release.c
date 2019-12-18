#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bi_private; } ;
struct TYPE_3__ {struct bio* bi_private; } ;
struct bio_pair {TYPE_2__ bio2; int /*<<< orphan*/  error; TYPE_1__ bio1; int /*<<< orphan*/  cnt; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct bio_pair*,int /*<<< orphan*/ ) ; 

void bio_pair_release(struct bio_pair *bp)
{
	if (atomic_dec_and_test(&bp->cnt)) {
		struct bio *master = bp->bio1.bi_private;

		bio_endio(master, bp->error);
		mempool_free(bp, bp->bio2.bi_private);
	}
}