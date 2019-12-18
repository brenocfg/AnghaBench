#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dtpv_arg; int /*<<< orphan*/  dtpv_pops; } ;
typedef  TYPE_1__ dtrace_provider_t ;
struct TYPE_5__ {int /*<<< orphan*/  dtpr_arg; TYPE_1__* dtpr_provider; int /*<<< orphan*/ * dtpr_ecb; } ;
typedef  TYPE_2__ dtrace_probe_t ;
typedef  int /*<<< orphan*/  dtrace_icookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  dtrace_interrupt_disable () ; 
 int /*<<< orphan*/  dtrace_interrupt_enable (int /*<<< orphan*/ ) ; 
 int dtrace_nprobes ; 
 TYPE_2__** dtrace_probes ; 

__attribute__((used)) static void
dtrace_probe_foreach(uintptr_t offs)
{
	dtrace_provider_t *prov;
	void (*func)(void *, dtrace_id_t, void *);
	dtrace_probe_t *probe;
	dtrace_icookie_t cookie;
	int i;

	/*
	 * We disable interrupts to walk through the probe array.  This is
	 * safe -- the dtrace_sync() in dtrace_unregister() assures that we
	 * won't see stale data.
	 */
	cookie = dtrace_interrupt_disable();

	for (i = 0; i < dtrace_nprobes; i++) {
		if ((probe = dtrace_probes[i]) == NULL)
			continue;

		if (probe->dtpr_ecb == NULL) {
			/*
			 * This probe isn't enabled -- don't call the function.
			 */
			continue;
		}

		prov = probe->dtpr_provider;
		func = *((void(**)(void *, dtrace_id_t, void *))
		    ((uintptr_t)&prov->dtpv_pops + offs));

		func(prov->dtpv_arg, i + 1, probe->dtpr_arg);
	}

	dtrace_interrupt_enable(cookie);
}