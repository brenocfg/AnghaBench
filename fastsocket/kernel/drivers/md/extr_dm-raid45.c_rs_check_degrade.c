#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stripe {int /*<<< orphan*/  sc; } ;
struct TYPE_2__ {unsigned int raid_devs; } ;
struct raid_set {TYPE_1__ set; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK (struct stripe*,unsigned int) ; 
 scalar_t__ ChunkError (int /*<<< orphan*/ ) ; 
 struct raid_set* RS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_check_degrade_dev (struct raid_set*,struct stripe*,unsigned int) ; 

__attribute__((used)) static void rs_check_degrade(struct stripe *stripe)
{
	struct raid_set *rs = RS(stripe->sc);
	unsigned p = rs->set.raid_devs;

	while (p--) {
		if (ChunkError(CHUNK(stripe, p)))
			rs_check_degrade_dev(rs, stripe, p);
	}
}