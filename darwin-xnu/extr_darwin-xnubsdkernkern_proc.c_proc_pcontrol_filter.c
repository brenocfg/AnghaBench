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
typedef  scalar_t__ uint64_t ;
struct no_paging_space {scalar_t__ pcs_max_size; scalar_t__ npcs_max_size; int /*<<< orphan*/  npcs_proc_count; int /*<<< orphan*/  npcs_total_size; int /*<<< orphan*/  npcs_uniqueid; int /*<<< orphan*/  npcs_pid; int /*<<< orphan*/  apcs_proc_count; int /*<<< orphan*/  apcs_total_size; int /*<<< orphan*/  pcs_proc_count; int /*<<< orphan*/  pcs_total_size; int /*<<< orphan*/  pcs_uniqueid; int /*<<< orphan*/  pcs_pid; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_5__ {int /*<<< orphan*/  p_uniqueid; int /*<<< orphan*/  p_pid; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 scalar_t__ PROC_ACTION_STATE (TYPE_1__*) ; 
 scalar_t__ PROC_CONTROL_STATE (TYPE_1__*) ; 
 scalar_t__ get_task_compressed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
proc_pcontrol_filter(proc_t p, void *arg)
{
	struct no_paging_space *nps;
	uint64_t	compressed;

	nps = (struct no_paging_space *)arg;

	compressed = get_task_compressed(p->task);

	if (PROC_CONTROL_STATE(p)) {
		if (PROC_ACTION_STATE(p) == 0) {
			if (compressed > nps->pcs_max_size) {
				nps->pcs_pid = p->p_pid;
				nps->pcs_uniqueid = p->p_uniqueid;
				nps->pcs_max_size = compressed;
			}
			nps->pcs_total_size += compressed;
			nps->pcs_proc_count++;
		} else {
			nps->apcs_total_size += compressed;
			nps->apcs_proc_count++;
		}
	} else {
		if (compressed > nps->npcs_max_size) {
			nps->npcs_pid = p->p_pid;
			nps->npcs_uniqueid = p->p_uniqueid;
			nps->npcs_max_size = compressed;
		}
		nps->npcs_total_size += compressed;
		nps->npcs_proc_count++;

	}
	return (0);
}