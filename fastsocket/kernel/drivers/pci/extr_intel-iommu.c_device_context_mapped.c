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
typedef  size_t u8 ;
struct root_entry {int dummy; } ;
struct intel_iommu {int /*<<< orphan*/  lock; struct root_entry* root_entry; } ;
struct context_entry {int dummy; } ;

/* Variables and functions */
 int context_present (struct context_entry*) ; 
 struct context_entry* get_context_addr_from_root (struct root_entry*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int device_context_mapped(struct intel_iommu *iommu, u8 bus, u8 devfn)
{
	struct root_entry *root;
	struct context_entry *context;
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&iommu->lock, flags);
	root = &iommu->root_entry[bus];
	context = get_context_addr_from_root(root);
	if (!context) {
		ret = 0;
		goto out;
	}
	ret = context_present(&context[devfn]);
out:
	spin_unlock_irqrestore(&iommu->lock, flags);
	return ret;
}