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
typedef  int /*<<< orphan*/  cpumask_var_t ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 scalar_t__ DISABLE_LISTEN_SPAWN ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*,...) ; 
 int EINVAL ; 
 scalar_t__ ENABLE_LISTEN_SPAWN_AUTOSET_AFFINITY ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  EPRINTK_LIMIT (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ERR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_isset (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_set (int,int /*<<< orphan*/ ) ; 
 int cpumask_first (int /*<<< orphan*/ ) ; 
 int cpumask_next (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 scalar_t__ enable_listen_spawn ; 
 int fastsocket_spawn_cpu ; 
 int /*<<< orphan*/  fastsocket_spawn_cpuset ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int nr_cpu_ids ; 
 int num_active_cpus () ; 
 int /*<<< orphan*/  sched_getaffinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsocket_process_affinity_check(int rcpu)
{
	int ccpu, ncpu, cpu;
	int tcpu = -1;
	cpumask_var_t omask;
	//struct socket *sock;

	if (enable_listen_spawn == DISABLE_LISTEN_SPAWN) {
		EPRINTK_LIMIT(ERR, "Module para disable listen-spawn feature\n");
		return -EPERM;
	}

	if ((rcpu >= 0) && (rcpu > num_active_cpus())) {
		EPRINTK_LIMIT(ERR, "Requested CPU %d is greater than system available CPU core %d\n", rcpu, num_active_cpus());
		return -EINVAL;
	}

	/* Respect the choice of user */

	if (rcpu >= 0)
		return rcpu;

	if (!alloc_cpumask_var(&omask, GFP_KERNEL))
		return -ENOMEM;

	sched_getaffinity(current->pid, omask);
	ccpu = cpumask_first(omask);
	ncpu = cpumask_next(ccpu, omask);
	free_cpumask_var(omask);

	DPRINTK(DEBUG, "Current process ccpu(%d) ncpu(%d)\n", ccpu, ncpu);

	if (ccpu >= nr_cpu_ids) {
		DPRINTK(DEBUG, "Current process affinity is messed up\n");
		return -EINVAL;
	}

	if (ncpu >= nr_cpu_ids) {
		DPRINTK(INFO, "Current process already binds to CPU %d\n", ccpu);
		return ccpu;
	}

	if (enable_listen_spawn != ENABLE_LISTEN_SPAWN_AUTOSET_AFFINITY) {
		EPRINTK_LIMIT(ERR, "Module para disable autoset affinity for listen-spawn\n");
		return -EPERM;
	}

	/* Choose a unused CPU core to bind this process */	

	for (cpu = fastsocket_spawn_cpu; cpu < num_active_cpus(); cpu++) {
		if (!cpu_isset(cpu, fastsocket_spawn_cpuset)) {
			DPRINTK(INFO, "CPU %d is available for process affinity\n", cpu);
			tcpu = cpu;
			break;
		}
	}

	if (tcpu >= 0) {
		cpu_set(cpu, fastsocket_spawn_cpuset);
		fastsocket_spawn_cpu++;
	} else {
		EPRINTK_LIMIT(ERR, "Process number is more than CPU number\n");
		return -EINVAL;
	}

	DPRINTK(INFO, "Target process affinity: %d\n", tcpu);

	return tcpu;
}