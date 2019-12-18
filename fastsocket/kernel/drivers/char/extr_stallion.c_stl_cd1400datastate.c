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
struct stlport {int /*<<< orphan*/  istate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYI_TXBUSY ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlport*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stl_cd1400datastate(struct stlport *portp)
{
	pr_debug("stl_cd1400datastate(portp=%p)\n", portp);

	if (portp == NULL)
		return 0;

	return test_bit(ASYI_TXBUSY, &portp->istate) ? 1 : 0;
}