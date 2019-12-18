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
struct t10_alua_lu_gp_member {int /*<<< orphan*/  lu_gp_mem_lock; } ;
struct se_device {TYPE_1__* transport; TYPE_2__* se_hba; } ;
struct TYPE_4__ {int hba_flags; } ;
struct TYPE_3__ {scalar_t__ transport_type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int HBA_FLAGS_INTERNAL_USE ; 
 scalar_t__ IS_ERR (struct t10_alua_lu_gp_member*) ; 
 int PTR_ERR (struct t10_alua_lu_gp_member*) ; 
 scalar_t__ TRANSPORT_PLUGIN_PHBA_PDEV ; 
 int /*<<< orphan*/  __core_alua_attach_lu_gp_mem (struct t10_alua_lu_gp_member*,int /*<<< orphan*/ ) ; 
 struct t10_alua_lu_gp_member* core_alua_allocate_lu_gp_mem (struct se_device*) ; 
 int /*<<< orphan*/  default_lu_gp ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int core_setup_alua(struct se_device *dev)
{
	if (dev->transport->transport_type != TRANSPORT_PLUGIN_PHBA_PDEV &&
	    !(dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE)) {
		struct t10_alua_lu_gp_member *lu_gp_mem;

		/*
		 * Associate this struct se_device with the default ALUA
		 * LUN Group.
		 */
		lu_gp_mem = core_alua_allocate_lu_gp_mem(dev);
		if (IS_ERR(lu_gp_mem))
			return PTR_ERR(lu_gp_mem);

		spin_lock(&lu_gp_mem->lu_gp_mem_lock);
		__core_alua_attach_lu_gp_mem(lu_gp_mem,
				default_lu_gp);
		spin_unlock(&lu_gp_mem->lu_gp_mem_lock);

		pr_debug("%s: Adding to default ALUA LU Group:"
			" core/alua/lu_gps/default_lu_gp\n",
			dev->transport->name);
	}

	return 0;
}