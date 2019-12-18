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
 int /*<<< orphan*/  TAINT_BIT_BY_ZOMBIE ; 
 int /*<<< orphan*/  WARN_TAINT (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int bitten_by_zombie(char *str)
{
	WARN_TAINT(1, TAINT_BIT_BY_ZOMBIE, "... ... ... BRAAAAIIIINNNNSSSSS\n");
	return 1;
}