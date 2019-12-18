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
typedef  int /*<<< orphan*/  uint64_t ;
struct dm_thin_device {int open_count; int /*<<< orphan*/  list; } ;
struct dm_pool_metadata {int /*<<< orphan*/  root; int /*<<< orphan*/  tl_info; int /*<<< orphan*/  details_root; int /*<<< orphan*/  details_info; } ;
typedef  int /*<<< orphan*/  dm_thin_id ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  __close_device (struct dm_thin_device*) ; 
 int __open_device (struct dm_pool_metadata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_thin_device**) ; 
 int dm_btree_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dm_thin_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __delete_device(struct dm_pool_metadata *pmd, dm_thin_id dev)
{
	int r;
	uint64_t key = dev;
	struct dm_thin_device *td;

	/* TODO: failure should mark the transaction invalid */
	r = __open_device(pmd, dev, 0, &td);
	if (r)
		return r;

	if (td->open_count > 1) {
		__close_device(td);
		return -EBUSY;
	}

	list_del(&td->list);
	kfree(td);
	r = dm_btree_remove(&pmd->details_info, pmd->details_root,
			    &key, &pmd->details_root);
	if (r)
		return r;

	r = dm_btree_remove(&pmd->tl_info, pmd->root, &key, &pmd->root);
	if (r)
		return r;

	return 0;
}