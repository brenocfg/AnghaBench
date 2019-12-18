#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_sec; } ;
struct no_paging_space {int npcs_proc_count; int npcs_max_size; int pcs_proc_count; int pcs_max_size; int apcs_proc_count; scalar_t__ npcs_uniqueid; scalar_t__ pcs_uniqueid; int /*<<< orphan*/  pcs_pid; int /*<<< orphan*/  npcs_pid; int /*<<< orphan*/  apcs_total_size; int /*<<< orphan*/  pcs_total_size; int /*<<< orphan*/  npcs_total_size; } ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  nps ;
struct TYPE_7__ {scalar_t__ p_uniqueid; int p_pid; char* p_comm; } ;

/* Variables and functions */
 int MB_SIZE ; 
 int /*<<< orphan*/  PROC_ALLPROCLIST ; 
 TYPE_1__* PROC_NULL ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (struct no_paging_space*,int) ; 
 struct timeval last_no_space_action ; 
 int /*<<< orphan*/  max_kill_priority ; 
 scalar_t__ memorystatus_get_proccnt_upto_priority (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memorystatus_kill_on_VM_compressor_space_shortage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  microtime (struct timeval*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  proc_dopcontrol (TYPE_1__*) ; 
 TYPE_1__* proc_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  proc_pcontrol_filter ; 
 int /*<<< orphan*/  proc_pcontrol_null ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  psignal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int vm_compressor_pages_compressed () ; 

int
no_paging_space_action()
{
	proc_t		p;
	struct no_paging_space nps;
	struct timeval	now;

	/*
	 * Throttle how often we come through here.  Once every 5 seconds should be plenty.
	 */
	microtime(&now);

	if (now.tv_sec <= last_no_space_action.tv_sec + 5)
		return (0);

	/*
	 * Examine all processes and find the biggest (biggest is based on the number of pages this 
	 * task has in the compressor pool) that has been marked to have some action
	 * taken when swap space runs out... we also find the biggest that hasn't been marked for
	 * action.
	 *
	 * If the biggest non-actionable task is over the "dangerously big" threashold (currently 50% of
	 * the total number of pages held by the compressor, we go ahead and kill it since no other task
	 * can have any real effect on the situation.  Otherwise, we go after the actionable process.
	 */
	bzero(&nps, sizeof(nps));

	proc_iterate(PROC_ALLPROCLIST, proc_pcontrol_null, (void *)NULL, proc_pcontrol_filter, (void *)&nps);

#if NO_PAGING_SPACE_DEBUG
	printf("low swap: npcs_proc_count = %d, npcs_total_size = %qd, npcs_max_size = %qd\n",
	       nps.npcs_proc_count, nps.npcs_total_size, nps.npcs_max_size);
	printf("low swap: pcs_proc_count = %d, pcs_total_size = %qd, pcs_max_size = %qd\n",
	       nps.pcs_proc_count, nps.pcs_total_size, nps.pcs_max_size);
	printf("low swap: apcs_proc_count = %d, apcs_total_size = %qd\n",
	       nps.apcs_proc_count, nps.apcs_total_size);
#endif
	if (nps.npcs_max_size > (vm_compressor_pages_compressed() * 50) / 100) {
		/*
		 * for now we'll knock out any task that has more then 50% of the pages
		 * held by the compressor
		 */
		if ((p = proc_find(nps.npcs_pid)) != PROC_NULL) {
	
			if (nps.npcs_uniqueid == p->p_uniqueid) {
				/*
				 * verify this is still the same process
				 * in case the proc exited and the pid got reused while
				 * we were finishing the proc_iterate and getting to this point
				 */
				last_no_space_action = now;

				printf("low swap: killing largest compressed process with pid %d (%s) and size %llu MB\n", p->p_pid, p->p_comm, (nps.pcs_max_size/MB_SIZE));
				psignal(p, SIGKILL);
			
				proc_rele(p);

				return (0);
			}
				
			proc_rele(p);
		}
	}

	/*
	 * We have some processes within our jetsam bands of consideration and hence can be killed.
	 * So we will invoke the memorystatus thread to go ahead and kill something.
	 */
	if (memorystatus_get_proccnt_upto_priority(max_kill_priority) > 0) {

		last_no_space_action = now;
		memorystatus_kill_on_VM_compressor_space_shortage(TRUE /* async */);
		return (1);
	}

	/*
	 * No eligible processes to kill. So let's suspend/kill the largest
	 * process depending on its policy control specifications.
	 */

	if (nps.pcs_max_size > 0) {
		if ((p = proc_find(nps.pcs_pid)) != PROC_NULL) {

			if (nps.pcs_uniqueid == p->p_uniqueid) {
				/*
				 * verify this is still the same process
				 * in case the proc exited and the pid got reused while
				 * we were finishing the proc_iterate and getting to this point
				 */
				last_no_space_action = now;
		
				proc_dopcontrol(p);
			
				proc_rele(p);
				
				return (1);
			}
	
			proc_rele(p);
		}
	}
	last_no_space_action = now;

	printf("low swap: unable to find any eligible processes to take action on\n");

	return (0);
}