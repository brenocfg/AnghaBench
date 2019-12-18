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
 int /*<<< orphan*/  PP_ATTR_REFERENCED ; 
 int /*<<< orphan*/  phys_attribute_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
pmap_is_referenced(
	ppnum_t pn)
{
	return phys_attribute_test(pn, PP_ATTR_REFERENCED);
}