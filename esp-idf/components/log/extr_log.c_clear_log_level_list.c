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
typedef  int /*<<< orphan*/  uncached_tag_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ s_log_cache_entry_count ; 
 scalar_t__ s_log_cache_max_generation ; 
 scalar_t__ s_log_cache_misses ; 
 int /*<<< orphan*/  s_log_tags ; 

void clear_log_level_list(void)
{
    uncached_tag_entry_t *it;
    while((it = SLIST_FIRST(&s_log_tags)) != NULL) {
        SLIST_REMOVE_HEAD(&s_log_tags, entries );
        free(it);
    }
    s_log_cache_entry_count = 0;
    s_log_cache_max_generation = 0;
#ifdef LOG_BUILTIN_CHECKS
    s_log_cache_misses = 0;
#endif
}