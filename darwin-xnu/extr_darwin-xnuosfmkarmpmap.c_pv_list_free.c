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
typedef  int /*<<< orphan*/  pv_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  PV_FREE_LIST (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
pv_list_free(
	pv_entry_t *pvehp,
	pv_entry_t *pvetp,
	unsigned int cnt)
{
	PV_FREE_LIST(pvehp, pvetp, cnt);
}