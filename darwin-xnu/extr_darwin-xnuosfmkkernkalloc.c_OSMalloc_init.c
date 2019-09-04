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

/* Variables and functions */
 int /*<<< orphan*/  LCK_ATTR_NULL ; 
 int /*<<< orphan*/  LCK_GRP_ATTR_NULL ; 
 int /*<<< orphan*/  OSMalloc_tag_lck_grp ; 
 int /*<<< orphan*/  OSMalloc_tag_list ; 
 int /*<<< orphan*/  OSMalloc_tag_lock ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 

void
OSMalloc_init(
	void)
{
	queue_init(&OSMalloc_tag_list);

	OSMalloc_tag_lck_grp = lck_grp_alloc_init("OSMalloc_tag", LCK_GRP_ATTR_NULL);
	lck_mtx_init(&OSMalloc_tag_lock, OSMalloc_tag_lck_grp, LCK_ATTR_NULL);
}