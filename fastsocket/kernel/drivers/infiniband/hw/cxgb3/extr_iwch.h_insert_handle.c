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
typedef  int u32 ;
struct iwch_dev {int /*<<< orphan*/  lock; } ;
struct idr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int idr_get_new_above (struct idr*,void*,int,int*) ; 
 int /*<<< orphan*/  idr_pre_get (struct idr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int insert_handle(struct iwch_dev *rhp, struct idr *idr,
				void *handle, u32 id)
{
	int ret;
	int newid;

	do {
		if (!idr_pre_get(idr, GFP_KERNEL)) {
			return -ENOMEM;
		}
		spin_lock_irq(&rhp->lock);
		ret = idr_get_new_above(idr, handle, id, &newid);
		BUG_ON(newid != id);
		spin_unlock_irq(&rhp->lock);
	} while (ret == -EAGAIN);

	return ret;
}