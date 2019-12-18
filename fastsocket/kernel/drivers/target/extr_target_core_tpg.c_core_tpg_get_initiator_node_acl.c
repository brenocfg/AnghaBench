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
struct se_portal_group {int /*<<< orphan*/  acl_node_lock; } ;
struct se_node_acl {int dummy; } ;

/* Variables and functions */
 struct se_node_acl* __core_tpg_get_initiator_node_acl (struct se_portal_group*,unsigned char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

struct se_node_acl *core_tpg_get_initiator_node_acl(
	struct se_portal_group *tpg,
	unsigned char *initiatorname)
{
	struct se_node_acl *acl;

	spin_lock_irq(&tpg->acl_node_lock);
	acl = __core_tpg_get_initiator_node_acl(tpg, initiatorname);
	spin_unlock_irq(&tpg->acl_node_lock);

	return acl;
}