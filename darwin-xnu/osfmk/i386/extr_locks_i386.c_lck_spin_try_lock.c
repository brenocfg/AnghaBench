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
typedef  int /*<<< orphan*/  usimple_lock_t ;
typedef  int /*<<< orphan*/  lck_spin_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  pltrace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usimple_lock_try (int /*<<< orphan*/ ) ; 

boolean_t
lck_spin_try_lock(
	lck_spin_t	*lck)
{
	boolean_t lrval = (boolean_t)usimple_lock_try((usimple_lock_t) lck);
#if	DEVELOPMENT || DEBUG
	if (lrval) {
		pltrace(FALSE);
	}
#endif
	return(lrval);
}