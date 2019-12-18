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
struct se_node_acl {struct se_dev_entry** device_list; } ;
struct se_dev_entry {int /*<<< orphan*/  ua_list; int /*<<< orphan*/  alua_port_list; int /*<<< orphan*/  ua_lock; int /*<<< orphan*/  pr_ref_count; int /*<<< orphan*/  ua_count; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int TRANSPORT_MAX_LUNS_PER_TPG ; 
 struct se_dev_entry** array_zalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int core_create_device_list_for_node(struct se_node_acl *nacl)
{
	struct se_dev_entry *deve;
	int i;

	nacl->device_list = array_zalloc(TRANSPORT_MAX_LUNS_PER_TPG,
			sizeof(struct se_dev_entry), GFP_KERNEL);
	if (!nacl->device_list) {
		pr_err("Unable to allocate memory for"
			" struct se_node_acl->device_list\n");
		return -ENOMEM;
	}
	for (i = 0; i < TRANSPORT_MAX_LUNS_PER_TPG; i++) {
		deve = nacl->device_list[i];

		atomic_set(&deve->ua_count, 0);
		atomic_set(&deve->pr_ref_count, 0);
		spin_lock_init(&deve->ua_lock);
		INIT_LIST_HEAD(&deve->alua_port_list);
		INIT_LIST_HEAD(&deve->ua_list);
	}

	return 0;
}