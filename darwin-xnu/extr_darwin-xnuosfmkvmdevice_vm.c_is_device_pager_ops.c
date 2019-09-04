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
struct memory_object_pager_ops {int dummy; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 struct memory_object_pager_ops const device_pager_ops ; 

boolean_t
is_device_pager_ops(const struct memory_object_pager_ops *pager_ops)
{
	if (pager_ops == &device_pager_ops) {
		return TRUE;
	}
	return FALSE;
}