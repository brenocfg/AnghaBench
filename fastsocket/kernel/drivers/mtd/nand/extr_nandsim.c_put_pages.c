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
struct nandsim {int held_cnt; int /*<<< orphan*/ * held_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  page_cache_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_pages(struct nandsim *ns)
{
	int i;

	for (i = 0; i < ns->held_cnt; i++)
		page_cache_release(ns->held_pages[i]);
}