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
struct dm_pool_metadata {int /*<<< orphan*/  data_space_map_root; int /*<<< orphan*/  data_sm; int /*<<< orphan*/  metadata_space_map_root; int /*<<< orphan*/  metadata_sm; } ;

/* Variables and functions */
 int dm_sm_copy_root (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int dm_sm_root_size (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int save_sm_roots(struct dm_pool_metadata *pmd)
{
	int r;
	size_t len;

	r = dm_sm_root_size(pmd->metadata_sm, &len);
	if (r < 0)
		return r;

	r = dm_sm_copy_root(pmd->metadata_sm, &pmd->metadata_space_map_root, len);
	if (r < 0)
		return r;

	r = dm_sm_root_size(pmd->data_sm, &len);
	if (r < 0)
		return r;

	return dm_sm_copy_root(pmd->data_sm, &pmd->data_space_map_root, len);
}