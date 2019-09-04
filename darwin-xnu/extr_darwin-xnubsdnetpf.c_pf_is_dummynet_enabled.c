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

__attribute__((used)) static inline boolean_t
pf_is_dummynet_enabled(void)
{
#if DUMMYNET
	if (__probable(!PF_IS_ENABLED))
		return (FALSE);

	if (__probable(!DUMMYNET_LOADED))
		return (FALSE);

	if (__probable(TAILQ_EMPTY(pf_main_ruleset.
	    rules[PF_RULESET_DUMMYNET].active.ptr)))
		return (FALSE);

	return (TRUE);
#else
	return (FALSE);
#endif /* DUMMYNET */
}