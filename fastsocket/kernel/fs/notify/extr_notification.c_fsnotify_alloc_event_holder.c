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
struct fsnotify_event_holder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fsnotify_event_holder_cachep ; 
 struct fsnotify_event_holder* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct fsnotify_event_holder *fsnotify_alloc_event_holder(void)
{
	return kmem_cache_alloc(fsnotify_event_holder_cachep, GFP_KERNEL);
}