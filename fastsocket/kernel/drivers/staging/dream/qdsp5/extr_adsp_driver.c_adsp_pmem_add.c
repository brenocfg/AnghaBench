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
struct msm_adsp_module {int /*<<< orphan*/  pmem_regions_lock; int /*<<< orphan*/  pmem_regions; } ;
struct file {int dummy; } ;
struct adsp_pmem_region {unsigned long paddr; unsigned long kvaddr; unsigned long len; int /*<<< orphan*/  list; struct file* file; int /*<<< orphan*/  vaddr; } ;
struct adsp_pmem_info {int /*<<< orphan*/  vaddr; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int adsp_pmem_check (struct msm_adsp_module*,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ get_pmem_file (int /*<<< orphan*/ ,unsigned long*,unsigned long*,unsigned long*,struct file**) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct adsp_pmem_region*) ; 
 struct adsp_pmem_region* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_pmem_file (struct file*) ; 

__attribute__((used)) static int adsp_pmem_add(struct msm_adsp_module *module,
			 struct adsp_pmem_info *info)
{
	unsigned long paddr, kvaddr, len;
	struct file *file;
	struct adsp_pmem_region *region;
	int rc = -EINVAL;

	mutex_lock(&module->pmem_regions_lock);
	region = kmalloc(sizeof(*region), GFP_KERNEL);
	if (!region) {
		rc = -ENOMEM;
		goto end;
	}
	INIT_HLIST_NODE(&region->list);
	if (get_pmem_file(info->fd, &paddr, &kvaddr, &len, &file)) {
		kfree(region);
		goto end;
	}

	rc = adsp_pmem_check(module, info->vaddr, len);
	if (rc < 0) {
		put_pmem_file(file);
		kfree(region);
		goto end;
	}

	region->vaddr = info->vaddr;
	region->paddr = paddr;
	region->kvaddr = kvaddr;
	region->len = len;
	region->file = file;

	hlist_add_head(&region->list, &module->pmem_regions);
end:
	mutex_unlock(&module->pmem_regions_lock);
	return rc;
}