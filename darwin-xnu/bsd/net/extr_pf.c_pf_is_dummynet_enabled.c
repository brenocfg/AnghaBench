#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {TYPE_2__* rules; } ;
struct TYPE_4__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_5__ {TYPE_1__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMMYNET_LOADED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PF_IS_ENABLED ; 
 size_t PF_RULESET_DUMMYNET ; 
 int TAILQ_EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ __probable (int) ; 
 TYPE_3__ pf_main_ruleset ; 

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