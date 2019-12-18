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
typedef  int /*<<< orphan*/  uint32_t ;
struct flow_divert_pcb {int /*<<< orphan*/  hash; } ;
struct flow_divert_group {int /*<<< orphan*/  lck; int /*<<< orphan*/  pcb_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDRETAIN (struct flow_divert_pcb*) ; 
 struct flow_divert_pcb* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  fd_pcb_tree ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct flow_divert_pcb *
flow_divert_pcb_lookup(uint32_t hash, struct flow_divert_group *group)
{
	struct flow_divert_pcb	key_item;
	struct flow_divert_pcb	*fd_cb		= NULL;

	key_item.hash = hash;

	lck_rw_lock_shared(&group->lck);
	fd_cb = RB_FIND(fd_pcb_tree, &group->pcb_tree, &key_item);
	FDRETAIN(fd_cb);
	lck_rw_done(&group->lck);

	return fd_cb;
}