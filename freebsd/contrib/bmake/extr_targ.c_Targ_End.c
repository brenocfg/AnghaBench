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
 int /*<<< orphan*/  Hash_DeleteTable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lst_Destroy (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TargFreeGN ; 
 scalar_t__ allGNs ; 
 scalar_t__ allTargets ; 
 int /*<<< orphan*/  targets ; 

void
Targ_End(void)
{
#ifdef CLEANUP
    Lst_Destroy(allTargets, NULL);
    if (allGNs)
	Lst_Destroy(allGNs, TargFreeGN);
    Hash_DeleteTable(&targets);
#endif
}