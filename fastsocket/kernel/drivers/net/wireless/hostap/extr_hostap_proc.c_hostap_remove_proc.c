#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* proc; TYPE_1__* ddev; } ;
typedef  TYPE_2__ local_info_t ;
struct TYPE_9__ {char* name; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_3__* hostap_proc ; 
 int /*<<< orphan*/  remove_proc_entry (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  remove_proc_subtree (int /*<<< orphan*/ ,TYPE_3__*) ; 

void hostap_remove_proc(local_info_t *local)
{
#if 0 /* Not in RHEL */
	remove_proc_subtree(local->ddev->name, hostap_proc);
#else
	if (local->proc != NULL) {
#ifndef PRISM2_NO_STATION_MODES
		remove_proc_entry("scan_results", local->proc);
#endif /* PRISM2_NO_STATION_MODES */
#ifdef PRISM2_IO_DEBUG
		remove_proc_entry("io_debug", local->proc);
#endif /* PRISM2_IO_DEBUG */
		remove_proc_entry("pda", local->proc);
		remove_proc_entry("aux_dump", local->proc);
		remove_proc_entry("wds", local->proc);
		remove_proc_entry("stats", local->proc);
		remove_proc_entry("bss_list", local->proc);
		remove_proc_entry("crypt", local->proc);
#ifndef PRISM2_NO_PROCFS_DEBUG
		remove_proc_entry("debug", local->proc);
#endif /* PRISM2_NO_PROCFS_DEBUG */
		if (hostap_proc != NULL)
			remove_proc_entry(local->proc->name, hostap_proc);
	}
#endif /* Not in RHEL */
}