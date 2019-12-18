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
struct raid_set {scalar_t__ dev; TYPE_1__ set; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK (struct stripe*,unsigned int) ; 
 int /*<<< orphan*/  DevFailed (scalar_t__) ; 
 struct raid_set* RS (int /*<<< orphan*/ ) ; 
 scalar_t__ chunk_io (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned for_each_io_dev(struct stripe *stripe,
			        void (*f_io)(struct stripe *stripe, unsigned p))
{
	struct raid_set *rs = RS(stripe->sc);
	unsigned p, r = 0;

	for (p = 0; p < rs->set.raid_devs; p++) {
		if (chunk_io(CHUNK(stripe, p)) && !DevFailed(rs->dev + p)) {
			f_io(stripe, p);
			r++;
		}
	}

	return r;
}