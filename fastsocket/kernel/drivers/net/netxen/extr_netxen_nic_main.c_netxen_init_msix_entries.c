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
struct netxen_adapter {TYPE_1__* msix_entries; } ;
struct TYPE_2__ {int entry; } ;

/* Variables and functions */

__attribute__((used)) static void netxen_init_msix_entries(struct netxen_adapter *adapter, int count)
{
	int i;

	for (i = 0; i < count; i++)
		adapter->msix_entries[i].entry = i;
}