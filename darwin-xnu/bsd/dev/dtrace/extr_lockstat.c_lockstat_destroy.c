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
struct TYPE_2__ {size_t lsp_probe; scalar_t__ lsp_id; } ;
typedef  TYPE_1__ lockstat_probe_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/ * lockstat_probemap ; 

__attribute__((used)) static void
lockstat_destroy(void *arg, dtrace_id_t id, void *parg)
{
#pragma unused(arg, id) /* __APPLE__ */
    
	lockstat_probe_t *probe = parg;

	ASSERT(!lockstat_probemap[probe->lsp_probe]);
	probe->lsp_id = 0;
}