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
struct se_portal_group {int dummy; } ;
struct se_node_acl {int dummy; } ;
struct ft_node_acl {struct se_node_acl se_node_acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ft_node_acl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct ft_node_acl*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

struct se_node_acl *ft_tpg_alloc_fabric_acl(struct se_portal_group *se_tpg)
{
	struct ft_node_acl *acl;

	acl = kzalloc(sizeof(*acl), GFP_KERNEL);
	if (!acl) {
		pr_err("Unable to allocate struct ft_node_acl\n");
		return NULL;
	}
	pr_debug("acl %p\n", acl);
	return &acl->se_node_acl;
}