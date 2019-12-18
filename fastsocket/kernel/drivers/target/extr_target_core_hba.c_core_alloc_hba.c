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
typedef  int /*<<< orphan*/  u32 ;
struct se_hba {TYPE_1__* transport; scalar_t__ hba_id; int /*<<< orphan*/  hba_node; int /*<<< orphan*/  hba_flags; int /*<<< orphan*/  hba_index; int /*<<< orphan*/  hba_access_mutex; int /*<<< orphan*/  device_lock; } ;
struct TYPE_2__ {int (* attach_hba ) (struct se_hba*,int /*<<< orphan*/ ) ;scalar_t__ owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct se_hba* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SCSI_INST_INDEX ; 
 TYPE_1__* core_get_backend (char const*) ; 
 int /*<<< orphan*/  hba_id_counter ; 
 int /*<<< orphan*/  hba_list ; 
 int /*<<< orphan*/  hba_lock ; 
 int /*<<< orphan*/  kfree (struct se_hba*) ; 
 struct se_hba* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (scalar_t__) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  scsi_get_new_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct se_hba*,int /*<<< orphan*/ ) ; 

struct se_hba *
core_alloc_hba(const char *plugin_name, u32 plugin_dep_id, u32 hba_flags)
{
	struct se_hba *hba;
	int ret = 0;

	hba = kzalloc(sizeof(*hba), GFP_KERNEL);
	if (!hba) {
		pr_err("Unable to allocate struct se_hba\n");
		return ERR_PTR(-ENOMEM);
	}

	spin_lock_init(&hba->device_lock);
	mutex_init(&hba->hba_access_mutex);

	hba->hba_index = scsi_get_new_index(SCSI_INST_INDEX);
	hba->hba_flags |= hba_flags;

	hba->transport = core_get_backend(plugin_name);
	if (!hba->transport) {
		ret = -EINVAL;
		goto out_free_hba;
	}

	ret = hba->transport->attach_hba(hba, plugin_dep_id);
	if (ret < 0)
		goto out_module_put;

	spin_lock(&hba_lock);
	hba->hba_id = hba_id_counter++;
	list_add_tail(&hba->hba_node, &hba_list);
	spin_unlock(&hba_lock);

	pr_debug("CORE_HBA[%d] - Attached HBA to Generic Target"
			" Core\n", hba->hba_id);

	return hba;

out_module_put:
	if (hba->transport->owner)
		module_put(hba->transport->owner);
	hba->transport = NULL;
out_free_hba:
	kfree(hba);
	return ERR_PTR(ret);
}