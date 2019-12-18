#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_call_func_t ;
struct sockaddr_ctl {int /*<<< orphan*/  sc_unit; } ;
struct TYPE_5__ {struct TYPE_5__* ncs_next; int /*<<< orphan*/  ncs_flags; int /*<<< orphan*/  ncs_unit; int /*<<< orphan*/  ncs_kctl; int /*<<< orphan*/  ncs_mtx; } ;
typedef  TYPE_1__ nstat_control_state ;
typedef  int /*<<< orphan*/  kern_ctl_ref ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int /*<<< orphan*/  NSTAT_FLAG_REQCOUNTS ; 
 TYPE_1__* OSMalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  clock_interval_to_deadline (int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* nstat_controls ; 
 scalar_t__ nstat_idle_check ; 
 scalar_t__ nstat_idle_time ; 
 int /*<<< orphan*/  nstat_lck_grp ; 
 int /*<<< orphan*/  nstat_malloc_tag ; 
 int /*<<< orphan*/  nstat_mtx ; 
 int /*<<< orphan*/  thread_call_func_delayed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static errno_t
nstat_control_connect(
	kern_ctl_ref		kctl,
	struct sockaddr_ctl	*sac,
	void				**uinfo)
{
	nstat_control_state	*state = OSMalloc(sizeof(*state), nstat_malloc_tag);
	if (state == NULL) return ENOMEM;

	bzero(state, sizeof(*state));
	lck_mtx_init(&state->ncs_mtx, nstat_lck_grp, NULL);
	state->ncs_kctl = kctl;
	state->ncs_unit = sac->sc_unit;
	state->ncs_flags = NSTAT_FLAG_REQCOUNTS;
	*uinfo = state;

	lck_mtx_lock(&nstat_mtx);
	state->ncs_next = nstat_controls;
	nstat_controls = state;

	if (nstat_idle_time == 0)
	{
		clock_interval_to_deadline(60, NSEC_PER_SEC, &nstat_idle_time);
		thread_call_func_delayed((thread_call_func_t)nstat_idle_check, NULL, nstat_idle_time);
	}

	lck_mtx_unlock(&nstat_mtx);

	return 0;
}