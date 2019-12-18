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
 int EINVAL ; 
 unsigned int MTRR_TYPE_UNCACHABLE ; 
 unsigned int MTRR_TYPE_WRCOMB ; 
 scalar_t__ centaur_mcr_type ; 
 int /*<<< orphan*/  pr_warning (char*,char*) ; 

__attribute__((used)) static int
centaur_validate_add_page(unsigned long base, unsigned long size, unsigned int type)
{
	/*
	 * FIXME: Winchip2 supports uncached
	 */
	if (type != MTRR_TYPE_WRCOMB &&
	    (centaur_mcr_type == 0 || type != MTRR_TYPE_UNCACHABLE)) {
		pr_warning("mtrr: only write-combining%s supported\n",
			   centaur_mcr_type ? " and uncacheable are" : " is");
		return -EINVAL;
	}
	return 0;
}