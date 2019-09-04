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
typedef  int /*<<< orphan*/  ppnum_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PHYS_REFERENCED ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ phys_attribute_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
pmap_is_referenced(ppnum_t pn)
{
        if (phys_attribute_test(pn, PHYS_REFERENCED))
		return TRUE;
	return FALSE;
}