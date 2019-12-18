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
struct dm_pool_metadata {int read_only; int /*<<< orphan*/  root_lock; int /*<<< orphan*/  bm; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_bm_set_read_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void dm_pool_metadata_read_write(struct dm_pool_metadata *pmd)
{
	down_write(&pmd->root_lock);
	pmd->read_only = false;
	dm_bm_set_read_write(pmd->bm);
	up_write(&pmd->root_lock);
}