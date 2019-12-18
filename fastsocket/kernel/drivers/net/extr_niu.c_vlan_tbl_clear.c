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
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_VLAN_TBL (int) ; 
 int ENET_VLAN_TBL_NUM_ENTRIES ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlan_tbl_clear(struct niu *np)
{
	int i;

	for (i = 0; i < ENET_VLAN_TBL_NUM_ENTRIES; i++)
		nw64(ENET_VLAN_TBL(i), 0);
}