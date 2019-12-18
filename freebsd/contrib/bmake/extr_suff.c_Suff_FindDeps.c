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
typedef  int /*<<< orphan*/  GNode ;

/* Variables and functions */
 int /*<<< orphan*/  SuffFindDeps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SuffRemoveSrc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srclist ; 

void
Suff_FindDeps(GNode *gn)
{

    SuffFindDeps(gn, srclist);
    while (SuffRemoveSrc(srclist))
	continue;
}