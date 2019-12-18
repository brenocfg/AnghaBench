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
struct ohci_hcd {int /*<<< orphan*/  debug_dir; int /*<<< orphan*/  debug_async; int /*<<< orphan*/  debug_periodic; int /*<<< orphan*/  debug_registers; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void remove_debug_files (struct ohci_hcd *ohci)
{
	debugfs_remove(ohci->debug_registers);
	debugfs_remove(ohci->debug_periodic);
	debugfs_remove(ohci->debug_async);
	debugfs_remove(ohci->debug_dir);
}