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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 

boolean_t
pf_is_nlc_enabled(void)
{
#if DUMMYNET
	if (__probable(!pf_is_dummynet_enabled()))
		return (FALSE);

	if (__probable(!is_nlc_enabled_glb))
		return (FALSE);

	return (TRUE);
#else
	return (FALSE);
#endif /* DUMMYNET */
}