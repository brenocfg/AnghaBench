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
typedef  scalar_t__ dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lockstat_hot_patch (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__* lockstat_probemap ; 
 int /*<<< orphan*/  membar_producer () ; 

__attribute__((used)) static int
lockstat_enable(void *arg, dtrace_id_t id, void *parg)
{
#pragma unused(arg) /* __APPLE__ */
    
	lockstat_probe_t *probe = parg;

	ASSERT(!lockstat_probemap[probe->lsp_probe]);

	lockstat_probemap[probe->lsp_probe] = id;
	membar_producer();

	lockstat_hot_patch(TRUE, probe->lsp_probe);
	membar_producer();
	return(0);

}