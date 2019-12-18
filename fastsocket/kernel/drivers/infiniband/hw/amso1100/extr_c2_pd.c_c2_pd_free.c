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
struct c2_pd {int /*<<< orphan*/  pd_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  table; } ;
struct c2_dev {TYPE_1__ pd_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void c2_pd_free(struct c2_dev *c2dev, struct c2_pd *pd)
{
	spin_lock(&c2dev->pd_table.lock);
	__clear_bit(pd->pd_id, c2dev->pd_table.table);
	spin_unlock(&c2dev->pd_table.lock);
}