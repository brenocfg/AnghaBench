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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_portid {int /*<<< orphan*/  node; int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  tipc_own_addr ; 

int tipc_ownidentity(u32 ref, struct tipc_portid *id)
{
	id->ref = ref;
	id->node = tipc_own_addr;
	return 0;
}