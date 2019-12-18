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
 int /*<<< orphan*/  DBG_LOW (char*,unsigned long) ; 

__attribute__((used)) static long beat_lpar_hpte_remove(unsigned long hpte_group)
{
	DBG_LOW("hpte_remove(group=%lx)\n", hpte_group);
	return -1;
}