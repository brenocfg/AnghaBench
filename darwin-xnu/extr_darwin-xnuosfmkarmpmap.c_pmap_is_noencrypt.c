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

boolean_t
pmap_is_noencrypt(
	ppnum_t pn)
{
#if DEVELOPMENT || DEBUG
	boolean_t result = FALSE;

	if (!pa_valid(ptoa(pn))) return FALSE;

	result = (phys_attribute_test(pn, PP_ATTR_NOENCRYPT));

	return result;
#else
#pragma unused(pn)
	return FALSE;
#endif
}