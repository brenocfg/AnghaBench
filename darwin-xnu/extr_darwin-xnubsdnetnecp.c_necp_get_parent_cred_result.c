#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * task_t ;
struct necp_socket_info {int /*<<< orphan*/  cred_result; } ;
typedef  int /*<<< orphan*/ * proc_t ;
typedef  int /*<<< orphan*/ * kauth_cred_t ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/ * coalition_t ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 int /*<<< orphan*/ * COALITION_NULL ; 
 int /*<<< orphan*/  COALITION_TYPE_JETSAM ; 
 int /*<<< orphan*/  PRIV_NET_PRIVILEGED_NECP_MATCH ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * coalition_get_leader (int /*<<< orphan*/ *) ; 
 scalar_t__ coalition_is_leader (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * current_proc () ; 
 int /*<<< orphan*/ * get_bsdtask_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kauth_cred_proc_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  priv_check_cred (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * proc_task (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_deallocate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
necp_get_parent_cred_result(proc_t proc, struct necp_socket_info *info)
{
	task_t task = proc_task(proc ? proc : current_proc());
	coalition_t coal = COALITION_NULL;
	Boolean is_leader = coalition_is_leader(task, COALITION_TYPE_JETSAM, &coal);

	if (is_leader == TRUE) {
		// No parent, nothing to do
		return;
	}

	if (coal != NULL) {
		task_t lead_task = coalition_get_leader(coal);
		if (lead_task != NULL) {
			proc_t lead_proc = get_bsdtask_info(lead_task);
			if (lead_proc != NULL) {
				kauth_cred_t lead_cred = kauth_cred_proc_ref(lead_proc);
				if (lead_cred != NULL) {
					errno_t cred_result = priv_check_cred(lead_cred, PRIV_NET_PRIVILEGED_NECP_MATCH, 0);
					kauth_cred_unref(&lead_cred);
					info->cred_result = cred_result;
				}
			}
			task_deallocate(lead_task);
		}
	}
}