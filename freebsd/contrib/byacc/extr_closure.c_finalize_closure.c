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
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  first_base ; 
 int /*<<< orphan*/  itemset ; 
 int /*<<< orphan*/  ruleset ; 

void
finalize_closure(void)
{
    FREE(itemset);
    FREE(ruleset);
    FREE(first_base);
}