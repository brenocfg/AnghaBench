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

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 void* Lst_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Suff_ClearSuffixes () ; 
 void* srclist ; 
 void* suffClean ; 
 void* transforms ; 

void
Suff_Init(void)
{
#ifdef CLEANUP
    suffClean = Lst_Init(FALSE);
#endif
    srclist = Lst_Init(FALSE);
    transforms = Lst_Init(FALSE);

    /*
     * Create null suffix for single-suffix rules (POSIX). The thing doesn't
     * actually go on the suffix list or everyone will think that's its
     * suffix.
     */
    Suff_ClearSuffixes();
}