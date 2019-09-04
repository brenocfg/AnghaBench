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
struct TYPE_2__ {size_t lsp_probe; } ;
typedef  TYPE_1__ lockstat_probe_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int LS_NPROBES ; 
 int /*<<< orphan*/  lockstat_hot_patch (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__* lockstat_probemap ; 
 int /*<<< orphan*/  membar_producer () ; 

__attribute__((used)) static void
lockstat_disable(void *arg, dtrace_id_t id, void *parg)
{
#pragma unused(arg, id) /* __APPLE__ */

	lockstat_probe_t *probe = parg;
	int i;

	ASSERT(lockstat_probemap[probe->lsp_probe]);

	lockstat_probemap[probe->lsp_probe] = 0;
	lockstat_hot_patch(FALSE, probe->lsp_probe);
	membar_producer();

	/*
	 * See if we have any probes left enabled.
	 */
	for (i = 0; i < LS_NPROBES; i++) {
		if (lockstat_probemap[i]) {
			/*
			 * This probe is still enabled.  We don't need to deal
			 * with waiting for all threads to be out of the
			 * lockstat critical sections; just return.
			 */
			return;
		}
	}

}