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
struct TYPE_4__ {int /*<<< orphan*/  lsp_name; int /*<<< orphan*/ * lsp_func; scalar_t__ lsp_id; } ;
typedef  TYPE_1__ lockstat_probe_t ;
typedef  int /*<<< orphan*/  dtrace_probedesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  LOCKSTAT_AFRAMES ; 
 scalar_t__ dtrace_probe_create (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ dtrace_probe_lookup (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockstat_id ; 
 TYPE_1__* lockstat_probes ; 

__attribute__((used)) static void
lockstat_provide(void *arg, const dtrace_probedesc_t *desc)
{
#pragma unused(arg, desc) /* __APPLE__ */
    
	int i = 0;

	for (i = 0; lockstat_probes[i].lsp_func != NULL; i++) {
		lockstat_probe_t *probe = &lockstat_probes[i];

		if (dtrace_probe_lookup(lockstat_id, "mach_kernel",
		    probe->lsp_func, probe->lsp_name) != 0)
			continue;

		ASSERT(!probe->lsp_id);
		probe->lsp_id = dtrace_probe_create(lockstat_id,
		    "mach_kernel", probe->lsp_func, probe->lsp_name,
		    LOCKSTAT_AFRAMES, probe);
	}
}