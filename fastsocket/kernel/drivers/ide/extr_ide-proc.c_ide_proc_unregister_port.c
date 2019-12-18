#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * proc; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  hwif_entries ; 
 int /*<<< orphan*/  ide_remove_proc_entries (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_ide_root ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ide_proc_unregister_port(ide_hwif_t *hwif)
{
	if (hwif->proc) {
		ide_remove_proc_entries(hwif->proc, hwif_entries);
		remove_proc_entry(hwif->name, proc_ide_root);
		hwif->proc = NULL;
	}
}