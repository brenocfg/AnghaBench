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
struct TYPE_2__ {int /*<<< orphan*/ * ci_array; } ;
struct ocfs2_caching_info {int ci_num_cached; TYPE_1__ ci_cache; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int OCFS2_CACHE_INFO_MAX_ARRAY ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void ocfs2_remove_metadata_array(struct ocfs2_caching_info *ci,
					int index)
{
	sector_t *array = ci->ci_cache.ci_array;
	int bytes;

	BUG_ON(index < 0 || index >= OCFS2_CACHE_INFO_MAX_ARRAY);
	BUG_ON(index >= ci->ci_num_cached);
	BUG_ON(!ci->ci_num_cached);

	mlog(0, "remove index %d (num_cached = %u\n", index,
	     ci->ci_num_cached);

	ci->ci_num_cached--;

	/* don't need to copy if the array is now empty, or if we
	 * removed at the tail */
	if (ci->ci_num_cached && index < ci->ci_num_cached) {
		bytes = sizeof(sector_t) * (ci->ci_num_cached - index);
		memmove(&array[index], &array[index + 1], bytes);
	}
}