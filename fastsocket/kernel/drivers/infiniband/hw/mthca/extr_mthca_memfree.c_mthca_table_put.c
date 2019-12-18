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
struct mthca_icm_table {int num_obj; int obj_size; int /*<<< orphan*/  mutex; TYPE_1__** icm; int /*<<< orphan*/  coherent; scalar_t__ virt; } ;
struct mthca_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ refcount; } ;

/* Variables and functions */
 int MTHCA_ICM_PAGE_SIZE ; 
 int MTHCA_TABLE_CHUNK_SIZE ; 
 int /*<<< orphan*/  mthca_UNMAP_ICM (struct mthca_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  mthca_free_icm (struct mthca_dev*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mthca_table_put(struct mthca_dev *dev, struct mthca_icm_table *table, int obj)
{
	int i;

	if (!mthca_is_memfree(dev))
		return;

	i = (obj & (table->num_obj - 1)) * table->obj_size / MTHCA_TABLE_CHUNK_SIZE;

	mutex_lock(&table->mutex);

	if (--table->icm[i]->refcount == 0) {
		mthca_UNMAP_ICM(dev, table->virt + i * MTHCA_TABLE_CHUNK_SIZE,
				MTHCA_TABLE_CHUNK_SIZE / MTHCA_ICM_PAGE_SIZE);
		mthca_free_icm(dev, table->icm[i], table->coherent);
		table->icm[i] = NULL;
	}

	mutex_unlock(&table->mutex);
}