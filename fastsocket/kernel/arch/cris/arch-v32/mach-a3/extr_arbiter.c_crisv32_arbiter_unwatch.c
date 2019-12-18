#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crisv32_watch_entry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int ARBITERS ; 
 int EINVAL ; 
 int NUMBER_OF_BP ; 
 int REG_RD_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arbiter_lock ; 
 int /*<<< orphan*/  crisv32_arbiter_init () ; 
 int /*<<< orphan*/  marb_bar ; 
 int /*<<< orphan*/  marb_foo ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regi_marb_bar ; 
 int /*<<< orphan*/  regi_marb_foo ; 
 int /*<<< orphan*/  rw_intr_mask ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__** watches ; 

int crisv32_arbiter_unwatch(int id)
{
	int arbiter;
	int intr_mask;

	crisv32_arbiter_init();

	spin_lock(&arbiter_lock);

	for (arbiter = 0; arbiter < ARBITERS; arbiter++) {
		int id2;

		if (arbiter)
			intr_mask = REG_RD_INT(marb_bar, regi_marb_bar,
				rw_intr_mask);
		else
			intr_mask = REG_RD_INT(marb_foo, regi_marb_foo,
				rw_intr_mask);

		id2 = (id & (0xff << (arbiter + 8))) >> (arbiter + 8);
		if (id2 == 0)
			continue;
		id2--;
		if ((id2 >= NUMBER_OF_BP) || (!watches[arbiter][id2].used)) {
			spin_unlock(&arbiter_lock);
			return -EINVAL;
		}

		memset(&watches[arbiter][id2], 0,
			sizeof(struct crisv32_watch_entry));

		if (id2 == 0)
			intr_mask &= ~1;
		else if (id2 == 1)
			intr_mask &= ~2;
		else if (id2 == 2)
			intr_mask &= ~4;
		else if (id2 == 3)
			intr_mask &= ~8;

		if (arbiter)
			REG_WR_INT(marb_bar, regi_marb_bar, rw_intr_mask,
				intr_mask);
		else
			REG_WR_INT(marb_foo, regi_marb_foo, rw_intr_mask,
				intr_mask);
	}

	spin_unlock(&arbiter_lock);
	return 0;
}