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
struct adapter {int /*<<< orphan*/ * debugfs_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void slic_debug_adapter_destroy(struct adapter *adapter)
{
	if (adapter->debugfs_entry) {
		debugfs_remove(adapter->debugfs_entry);
		adapter->debugfs_entry = NULL;
	}
}