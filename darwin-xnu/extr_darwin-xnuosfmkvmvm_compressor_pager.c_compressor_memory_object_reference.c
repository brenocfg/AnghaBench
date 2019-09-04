#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  memory_object_t ;
typedef  TYPE_1__* compressor_pager_t ;
struct TYPE_5__ {scalar_t__ cpgr_references; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  compressor_pager_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  compressor_pager_lookup (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  compressor_pager_unlock (TYPE_1__*) ; 

void
compressor_memory_object_reference(
	memory_object_t		mem_obj)
{
	compressor_pager_t	pager;

	compressor_pager_lookup(mem_obj, pager);
	if (pager == NULL)
		return;

	compressor_pager_lock(pager);
	assert(pager->cpgr_references > 0);
	pager->cpgr_references++;
	compressor_pager_unlock(pager);
}