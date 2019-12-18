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
 int /*<<< orphan*/  CPLD_DS_ENABLE ; 
 int /*<<< orphan*/  nw_cpld_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void netwinder_ds1620_reset(void)
{
	nw_cpld_modify(CPLD_DS_ENABLE, 0);
	nw_cpld_modify(CPLD_DS_ENABLE, CPLD_DS_ENABLE);
}