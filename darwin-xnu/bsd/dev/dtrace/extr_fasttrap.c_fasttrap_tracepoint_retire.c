#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  p_pid; } ;
typedef  TYPE_1__ proc_t ;
struct TYPE_12__ {int ftt_retired; int /*<<< orphan*/  ftt_pc; } ;
typedef  TYPE_2__ fasttrap_tracepoint_t ;
struct TYPE_13__ {int /*<<< orphan*/  fttps_pc; int /*<<< orphan*/  fttps_pid; } ;
typedef  TYPE_3__ fasttrap_tracepoint_spec_t ;

/* Variables and functions */
 int /*<<< orphan*/  FASTTRAP_CLEANUP_TRACEPOINT ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int fasttrap_cur_retired ; 
 int /*<<< orphan*/  fasttrap_pid_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fasttrap_retired_mtx ; 
 int fasttrap_retired_size ; 
 TYPE_3__* fasttrap_retired_spec ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 TYPE_3__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 

void
fasttrap_tracepoint_retire(proc_t *p, fasttrap_tracepoint_t *tp)
{
	if (tp->ftt_retired)
		return;
	lck_mtx_lock(&fasttrap_retired_mtx);
	fasttrap_tracepoint_spec_t *s = &fasttrap_retired_spec[fasttrap_cur_retired++];
	s->fttps_pid = p->p_pid;
	s->fttps_pc = tp->ftt_pc;

	if (fasttrap_cur_retired == fasttrap_retired_size) {
		fasttrap_tracepoint_spec_t *new_retired = kmem_zalloc(
					fasttrap_retired_size * 2 *
					sizeof(*fasttrap_retired_spec),
					KM_SLEEP);
		memcpy(new_retired, fasttrap_retired_spec, sizeof(*fasttrap_retired_spec) * fasttrap_retired_size);
		kmem_free(fasttrap_retired_spec, sizeof(*fasttrap_retired_spec) * fasttrap_retired_size);
		fasttrap_retired_size *= 2;
		fasttrap_retired_spec = new_retired;
	}

	lck_mtx_unlock(&fasttrap_retired_mtx);

	tp->ftt_retired = 1;

	fasttrap_pid_cleanup(FASTTRAP_CLEANUP_TRACEPOINT);
}