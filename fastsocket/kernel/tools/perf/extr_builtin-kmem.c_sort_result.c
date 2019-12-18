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
 int /*<<< orphan*/  __sort_result (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alloc_sort ; 
 int /*<<< orphan*/  caller_sort ; 
 int /*<<< orphan*/  root_alloc_sorted ; 
 int /*<<< orphan*/  root_alloc_stat ; 
 int /*<<< orphan*/  root_caller_sorted ; 
 int /*<<< orphan*/  root_caller_stat ; 

__attribute__((used)) static void sort_result(void)
{
	__sort_result(&root_alloc_stat, &root_alloc_sorted, &alloc_sort);
	__sort_result(&root_caller_stat, &root_caller_sorted, &caller_sort);
}