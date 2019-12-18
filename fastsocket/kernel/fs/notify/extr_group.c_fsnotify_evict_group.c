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
struct fsnotify_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fsnotify_evict_group (struct fsnotify_group*) ; 
 int /*<<< orphan*/  fsnotify_grp_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void fsnotify_evict_group(struct fsnotify_group *group)
{
	mutex_lock(&fsnotify_grp_mutex);
	__fsnotify_evict_group(group);
	mutex_unlock(&fsnotify_grp_mutex);
}