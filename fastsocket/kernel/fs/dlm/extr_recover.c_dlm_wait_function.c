#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {long data; scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct dlm_ls {TYPE_1__ ls_timer; int /*<<< orphan*/  ls_wait_general; } ;
struct TYPE_6__ {int ci_recover_timer; } ;

/* Variables and functions */
 int EINTR ; 
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_1__*) ; 
 TYPE_2__ dlm_config ; 
 scalar_t__ dlm_recovery_stopped (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_wait_timer_fn ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  log_debug (struct dlm_ls*,char*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int dlm_wait_function(struct dlm_ls *ls, int (*testfn) (struct dlm_ls *ls))
{
	int error = 0;

	init_timer(&ls->ls_timer);
	ls->ls_timer.function = dlm_wait_timer_fn;
	ls->ls_timer.data = (long) ls;
	ls->ls_timer.expires = jiffies + (dlm_config.ci_recover_timer * HZ);
	add_timer(&ls->ls_timer);

	wait_event(ls->ls_wait_general, testfn(ls) || dlm_recovery_stopped(ls));
	del_timer_sync(&ls->ls_timer);

	if (dlm_recovery_stopped(ls)) {
		log_debug(ls, "dlm_wait_function aborted");
		error = -EINTR;
	}
	return error;
}