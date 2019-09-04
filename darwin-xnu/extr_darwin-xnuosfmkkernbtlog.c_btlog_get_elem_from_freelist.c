#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * freelist_elements; } ;
typedef  TYPE_1__ btlog_t ;
typedef  int /*<<< orphan*/  btlog_element_t ;

/* Variables and functions */
 uintptr_t BTLOG_HASHELEMINDEX_NONE ; 
 int /*<<< orphan*/  btlog_evict_elements_from_record (TYPE_1__*,int) ; 

btlog_element_t*
btlog_get_elem_from_freelist(btlog_t *btlog)
{
	btlog_element_t *free_elem = NULL;

retry:
	free_elem = btlog->freelist_elements;

	if ((uintptr_t)free_elem == BTLOG_HASHELEMINDEX_NONE) {
		/* nothing on freelist */
		btlog_evict_elements_from_record(btlog, 1);
		goto retry;
	} else {
		/* remove the head of the freelist */
		uintptr_t next_elem = *(uintptr_t*)free_elem;
		btlog->freelist_elements = (btlog_element_t *)next_elem;
		return free_elem;
	}
}