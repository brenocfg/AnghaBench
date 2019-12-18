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
typedef  scalar_t__ u16 ;
struct ib_sa_mcmember_rec {int /*<<< orphan*/  mgid; int /*<<< orphan*/  pkey; } ;
struct mcast_group {scalar_t__ state; scalar_t__ pkey_index; int /*<<< orphan*/  work; TYPE_2__* port; int /*<<< orphan*/  node; struct ib_sa_mcmember_rec rec; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  table; int /*<<< orphan*/  port_num; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ MCAST_BUSY ; 
 scalar_t__ MCAST_INVALID_PKEY_INDEX ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_find_pkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mcast_insert (TYPE_2__*,struct mcast_group*,int) ; 
 int /*<<< orphan*/  mcast_work_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mgid0 ; 
 int /*<<< orphan*/  process_join_error (struct mcast_group*,int) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void join_handler(int status, struct ib_sa_mcmember_rec *rec,
			 void *context)
{
	struct mcast_group *group = context;
	u16 pkey_index = MCAST_INVALID_PKEY_INDEX;

	if (status)
		process_join_error(group, status);
	else {
		ib_find_pkey(group->port->dev->device, group->port->port_num,
			     be16_to_cpu(rec->pkey), &pkey_index);

		spin_lock_irq(&group->port->lock);
		group->rec = *rec;
		if (group->state == MCAST_BUSY &&
		    group->pkey_index == MCAST_INVALID_PKEY_INDEX)
			group->pkey_index = pkey_index;
		if (!memcmp(&mgid0, &group->rec.mgid, sizeof mgid0)) {
			rb_erase(&group->node, &group->port->table);
			mcast_insert(group->port, group, 1);
		}
		spin_unlock_irq(&group->port->lock);
	}
	mcast_work_handler(&group->work);
}