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
struct t10_alua_lu_gp_member {struct se_device* lu_gp_mem_dev; int /*<<< orphan*/  lu_gp_mem_ref_cnt; int /*<<< orphan*/  lu_gp_mem_lock; int /*<<< orphan*/  lu_gp_mem_list; } ;
struct se_device {struct t10_alua_lu_gp_member* dev_alua_lu_gp_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct t10_alua_lu_gp_member* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct t10_alua_lu_gp_member* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t10_alua_lu_gp_mem_cache ; 

__attribute__((used)) static struct t10_alua_lu_gp_member *
core_alua_allocate_lu_gp_mem(struct se_device *dev)
{
	struct t10_alua_lu_gp_member *lu_gp_mem;

	lu_gp_mem = kmem_cache_zalloc(t10_alua_lu_gp_mem_cache, GFP_KERNEL);
	if (!lu_gp_mem) {
		pr_err("Unable to allocate struct t10_alua_lu_gp_member\n");
		return ERR_PTR(-ENOMEM);
	}
	INIT_LIST_HEAD(&lu_gp_mem->lu_gp_mem_list);
	spin_lock_init(&lu_gp_mem->lu_gp_mem_lock);
	atomic_set(&lu_gp_mem->lu_gp_mem_ref_cnt, 0);

	lu_gp_mem->lu_gp_mem_dev = dev;
	dev->dev_alua_lu_gp_mem = lu_gp_mem;

	return lu_gp_mem;
}