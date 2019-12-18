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
 int /*<<< orphan*/  Lst_Destroy (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  SuffFree (scalar_t__) ; 
 int /*<<< orphan*/  srclist ; 
 int /*<<< orphan*/  suffClean ; 
 scalar_t__ suffNull ; 
 int /*<<< orphan*/  sufflist ; 
 int /*<<< orphan*/  transforms ; 

void
Suff_End(void)
{
#ifdef CLEANUP
    Lst_Destroy(sufflist, SuffFree);
    Lst_Destroy(suffClean, SuffFree);
    if (suffNull)
	SuffFree(suffNull);
    Lst_Destroy(srclist, NULL);
    Lst_Destroy(transforms, NULL);
#endif
}