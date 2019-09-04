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

/* Variables and functions */

void
pmap_clear_noencrypt(
	ppnum_t pn)
{
#if DEVELOPMENT || DEBUG
	if (!pa_valid(ptoa(pn))) return;

	phys_attribute_clear(pn, PP_ATTR_NOENCRYPT, 0, NULL);
#else
#pragma unused(pn)
#endif
}