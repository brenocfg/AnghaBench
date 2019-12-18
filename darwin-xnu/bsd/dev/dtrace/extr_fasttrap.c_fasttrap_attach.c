#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong_t ;
typedef  int /*<<< orphan*/  fasttrap_bucket_t ;
struct TYPE_12__ {int fth_nent; int fth_mask; TYPE_3__* fth_table; } ;
struct TYPE_11__ {int fth_nent; int fth_mask; TYPE_2__* fth_table; } ;
struct TYPE_10__ {int fth_nent; int fth_mask; TYPE_1__* fth_table; } ;
struct TYPE_9__ {int /*<<< orphan*/  ftb_mtx; } ;
struct TYPE_8__ {int /*<<< orphan*/  ftb_mtx; } ;
struct TYPE_7__ {int /*<<< orphan*/  ftb_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DDI_DEV_T_ANY ; 
 int /*<<< orphan*/  DDI_PROP_DONTPASS ; 
 int FASTTRAP_PROCS_DEFAULT_SIZE ; 
 int FASTTRAP_PROVIDERS_DEFAULT_SIZE ; 
 int FASTTRAP_TPOINTS_DEFAULT_SIZE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int ddi_getprop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  devi ; 
 int /*<<< orphan*/ * dtrace_fasttrap_exec_ptr ; 
 int /*<<< orphan*/ * dtrace_fasttrap_exit_ptr ; 
 int /*<<< orphan*/ * dtrace_fasttrap_fork_ptr ; 
 int /*<<< orphan*/  dtrace_meta_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fasttrap_exec_exit ; 
 int /*<<< orphan*/  fasttrap_fork ; 
 int fasttrap_highbit (int) ; 
 int /*<<< orphan*/  fasttrap_lck_attr ; 
 int /*<<< orphan*/  fasttrap_lck_grp ; 
 int fasttrap_max ; 
 int /*<<< orphan*/  fasttrap_meta_id ; 
 int /*<<< orphan*/  fasttrap_mops ; 
 TYPE_6__ fasttrap_procs ; 
 TYPE_5__ fasttrap_provs ; 
 scalar_t__ fasttrap_retired ; 
 scalar_t__ fasttrap_total ; 
 TYPE_4__ fasttrap_tpoints ; 
 void* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sane_size ; 

__attribute__((used)) static void
fasttrap_attach(void)
{
	ulong_t nent;
	unsigned int i;

	/*
	 * Install our hooks into fork(2), exec(2), and exit(2).
	 */
	dtrace_fasttrap_fork_ptr = &fasttrap_fork;
	dtrace_fasttrap_exit_ptr = &fasttrap_exec_exit;
	dtrace_fasttrap_exec_ptr = &fasttrap_exec_exit;

	/*
	 * APPLE NOTE:  We size the maximum number of fasttrap probes
	 * based on system memory. 100k probes per 256M of system memory.
	 * Yes, this is a WAG.
	 */
	fasttrap_max = (sane_size >> 28) * 100000;

	if (fasttrap_max == 0)
		fasttrap_max = 50000;

	fasttrap_total = 0;
	fasttrap_retired = 0;

	/*
	 * Conjure up the tracepoints hashtable...
	 */
#ifdef illumos
	nent = ddi_getprop(DDI_DEV_T_ANY, devi, DDI_PROP_DONTPASS,
	    "fasttrap-hash-size", FASTTRAP_TPOINTS_DEFAULT_SIZE);
#else
	nent = FASTTRAP_TPOINTS_DEFAULT_SIZE;
#endif

	if (nent <= 0 || nent > 0x1000000)
		nent = FASTTRAP_TPOINTS_DEFAULT_SIZE;

	if ((nent & (nent - 1)) == 0)
		fasttrap_tpoints.fth_nent = nent;
	else
		fasttrap_tpoints.fth_nent = 1 << fasttrap_highbit(nent);
	ASSERT(fasttrap_tpoints.fth_nent > 0);
	fasttrap_tpoints.fth_mask = fasttrap_tpoints.fth_nent - 1;
	fasttrap_tpoints.fth_table = kmem_zalloc(fasttrap_tpoints.fth_nent *
	    sizeof (fasttrap_bucket_t), KM_SLEEP);
	ASSERT(fasttrap_tpoints.fth_table != NULL);

	for (i = 0; i < fasttrap_tpoints.fth_nent; i++) {
		lck_mtx_init(&fasttrap_tpoints.fth_table[i].ftb_mtx, fasttrap_lck_grp, fasttrap_lck_attr);
	}

	/*
	 * ... and the providers hash table...
	 */
	nent = FASTTRAP_PROVIDERS_DEFAULT_SIZE;
	if ((nent & (nent - 1)) == 0)
		fasttrap_provs.fth_nent = nent;
	else
		fasttrap_provs.fth_nent = 1 << fasttrap_highbit(nent);
	ASSERT(fasttrap_provs.fth_nent > 0);
	fasttrap_provs.fth_mask = fasttrap_provs.fth_nent - 1;
	fasttrap_provs.fth_table = kmem_zalloc(fasttrap_provs.fth_nent *
	    sizeof (fasttrap_bucket_t), KM_SLEEP);
	ASSERT(fasttrap_provs.fth_table != NULL);

	for (i = 0; i < fasttrap_provs.fth_nent; i++) {
		lck_mtx_init(&fasttrap_provs.fth_table[i].ftb_mtx, fasttrap_lck_grp, fasttrap_lck_attr);
	}

	/*
	 * ... and the procs hash table.
	 */
	nent = FASTTRAP_PROCS_DEFAULT_SIZE;
	if ((nent & (nent - 1)) == 0)
		fasttrap_procs.fth_nent = nent;
	else
		fasttrap_procs.fth_nent = 1 << fasttrap_highbit(nent);
	ASSERT(fasttrap_procs.fth_nent > 0);
	fasttrap_procs.fth_mask = fasttrap_procs.fth_nent - 1;
	fasttrap_procs.fth_table = kmem_zalloc(fasttrap_procs.fth_nent *
	    sizeof (fasttrap_bucket_t), KM_SLEEP);
	ASSERT(fasttrap_procs.fth_table != NULL);

#ifndef illumos
	for (i = 0; i < fasttrap_procs.fth_nent; i++) {
		lck_mtx_init(&fasttrap_procs.fth_table[i].ftb_mtx, fasttrap_lck_grp, fasttrap_lck_attr);
	}
#endif

	(void) dtrace_meta_register("fasttrap", &fasttrap_mops, NULL,
	    &fasttrap_meta_id);
}