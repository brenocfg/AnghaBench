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
typedef  int /*<<< orphan*/  u64 ;
struct ocrdma_ucontext {int /*<<< orphan*/  mm_list_lock; int /*<<< orphan*/  mm_head; } ;
struct TYPE_2__ {unsigned long len; int /*<<< orphan*/  phy_addr; } ;
struct ocrdma_mm {int /*<<< orphan*/  entry; TYPE_1__ key; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ocrdma_mm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocrdma_add_mmap(struct ocrdma_ucontext *uctx, u64 phy_addr,
			   unsigned long len)
{
	struct ocrdma_mm *mm;

	mm = kzalloc(sizeof(*mm), GFP_KERNEL);
	if (mm == NULL)
		return -ENOMEM;
	mm->key.phy_addr = phy_addr;
	mm->key.len = len;
	INIT_LIST_HEAD(&mm->entry);

	mutex_lock(&uctx->mm_list_lock);
	list_add_tail(&mm->entry, &uctx->mm_head);
	mutex_unlock(&uctx->mm_list_lock);
	return 0;
}