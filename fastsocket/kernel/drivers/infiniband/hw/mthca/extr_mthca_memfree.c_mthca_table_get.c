#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mthca_icm_table {int num_obj; int obj_size; int /*<<< orphan*/  mutex; TYPE_1__** icm; int /*<<< orphan*/  coherent; scalar_t__ virt; scalar_t__ lowmem; } ;
struct mthca_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_HIGHUSER ; 
 int GFP_KERNEL ; 
 int MTHCA_TABLE_CHUNK_SIZE ; 
 int PAGE_SHIFT ; 
 int __GFP_NOWARN ; 
 scalar_t__ mthca_MAP_ICM (struct mthca_dev*,TYPE_1__*,scalar_t__) ; 
 TYPE_1__* mthca_alloc_icm (struct mthca_dev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_free_icm (struct mthca_dev*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mthca_table_get(struct mthca_dev *dev, struct mthca_icm_table *table, int obj)
{
	int i = (obj & (table->num_obj - 1)) * table->obj_size / MTHCA_TABLE_CHUNK_SIZE;
	int ret = 0;

	mutex_lock(&table->mutex);

	if (table->icm[i]) {
		++table->icm[i]->refcount;
		goto out;
	}

	table->icm[i] = mthca_alloc_icm(dev, MTHCA_TABLE_CHUNK_SIZE >> PAGE_SHIFT,
					(table->lowmem ? GFP_KERNEL : GFP_HIGHUSER) |
					__GFP_NOWARN, table->coherent);
	if (!table->icm[i]) {
		ret = -ENOMEM;
		goto out;
	}

	if (mthca_MAP_ICM(dev, table->icm[i],
			  table->virt + i * MTHCA_TABLE_CHUNK_SIZE)) {
		mthca_free_icm(dev, table->icm[i], table->coherent);
		table->icm[i] = NULL;
		ret = -ENOMEM;
		goto out;
	}

	++table->icm[i]->refcount;

out:
	mutex_unlock(&table->mutex);
	return ret;
}