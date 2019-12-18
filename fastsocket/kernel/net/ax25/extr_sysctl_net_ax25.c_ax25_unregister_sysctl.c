#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* child; scalar_t__ ctl_name; } ;
typedef  TYPE_1__ ctl_table ;

/* Variables and functions */
 TYPE_1__* ax25_table ; 
 int /*<<< orphan*/  ax25_table_header ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  unregister_sysctl_table (int /*<<< orphan*/ ) ; 

void ax25_unregister_sysctl(void)
{
	ctl_table *p;
	unregister_sysctl_table(ax25_table_header);

	for (p = ax25_table; p->ctl_name; p++)
		kfree(p->child);
	kfree(ax25_table);
}