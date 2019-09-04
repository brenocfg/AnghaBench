#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  memory_object_t ;
typedef  TYPE_1__* apple_protect_pager_t ;
struct TYPE_3__ {scalar_t__ ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  apple_protect_pager_lock ; 
 TYPE_1__* apple_protect_pager_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

void
apple_protect_pager_reference(
	memory_object_t		mem_obj)
{	
	apple_protect_pager_t	pager;

	pager = apple_protect_pager_lookup(mem_obj);

	lck_mtx_lock(&apple_protect_pager_lock);
	assert(pager->ref_count > 0);
	pager->ref_count++;
	lck_mtx_unlock(&apple_protect_pager_lock);
}