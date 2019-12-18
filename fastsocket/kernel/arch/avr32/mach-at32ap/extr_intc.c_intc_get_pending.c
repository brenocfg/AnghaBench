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
 scalar_t__ INTREQ0 ; 
 int /*<<< orphan*/  intc0 ; 
 unsigned long intc_readl (int /*<<< orphan*/ *,scalar_t__) ; 

unsigned long intc_get_pending(unsigned int group)
{
	return intc_readl(&intc0, INTREQ0 + 4 * group);
}