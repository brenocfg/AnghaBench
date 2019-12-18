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
typedef  scalar_t__ uint64_t ;
struct dm_pool_metadata {scalar_t__ trans_id; int /*<<< orphan*/  root_lock; scalar_t__ fail_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int dm_pool_set_metadata_transaction_id(struct dm_pool_metadata *pmd,
					uint64_t current_id,
					uint64_t new_id)
{
	int r = -EINVAL;

	down_write(&pmd->root_lock);

	if (pmd->fail_io)
		goto out;

	if (pmd->trans_id != current_id) {
		DMERR("mismatched transaction id");
		goto out;
	}

	pmd->trans_id = new_id;
	r = 0;

out:
	up_write(&pmd->root_lock);

	return r;
}