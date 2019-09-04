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
 int /*<<< orphan*/  M_DQUOT ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  desiredvnodes ; 
 int /*<<< orphan*/  dq_list_lock () ; 
 int /*<<< orphan*/  dq_list_unlock () ; 
 int /*<<< orphan*/  dqdirtylist ; 
 int /*<<< orphan*/  dqfreelist ; 
 int /*<<< orphan*/  dqhash ; 
 int /*<<< orphan*/  dqhashtbl ; 
 scalar_t__ dqisinitialized () ; 
 int /*<<< orphan*/  hashinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
dqhashinit(void)
{
	dq_list_lock();
	if (dqisinitialized())
		goto out;

	TAILQ_INIT(&dqfreelist);
	TAILQ_INIT(&dqdirtylist);
	dqhashtbl = hashinit(desiredvnodes, M_DQUOT, &dqhash);
out:
	dq_list_unlock();
}