#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hlist_head {int dummy; } ;
struct TYPE_2__ {scalar_t__ local_publ_count; int /*<<< orphan*/  types; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ table ; 
 int /*<<< orphan*/  tipc_nametbl_size ; 

int tipc_nametbl_init(void)
{
	table.types = kcalloc(tipc_nametbl_size, sizeof(struct hlist_head),
			      GFP_ATOMIC);
	if (!table.types)
		return -ENOMEM;

	table.local_publ_count = 0;
	return 0;
}