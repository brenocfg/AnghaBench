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
struct task_struct {struct task_struct* rq_task; } ;
struct svc_serv {int sv_nrthreads; int sv_nrpools; int /*<<< orphan*/  sv_module; int /*<<< orphan*/  sv_name; int /*<<< orphan*/  sv_function; } ;
struct svc_rqst {struct svc_rqst* rq_task; } ;
struct svc_pool {int /*<<< orphan*/  sp_id; int /*<<< orphan*/  sp_lock; scalar_t__ sp_nrthreads; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 struct svc_pool* choose_pool (struct svc_serv*,struct svc_pool*,unsigned int*) ; 
 struct task_struct* choose_victim (struct svc_serv*,struct svc_pool*,unsigned int*) ; 
 struct task_struct* kthread_create (int /*<<< orphan*/ ,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,struct task_struct*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_exit_thread (struct task_struct*) ; 
 int /*<<< orphan*/  svc_pool_map_set_cpumask (struct task_struct*,int /*<<< orphan*/ ) ; 
 struct task_struct* svc_prepare_thread (struct svc_serv*,struct svc_pool*) ; 
 int /*<<< orphan*/  svc_sock_update_bufs (struct svc_serv*) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

int
svc_set_num_threads(struct svc_serv *serv, struct svc_pool *pool, int nrservs)
{
	struct svc_rqst	*rqstp;
	struct task_struct *task;
	struct svc_pool *chosen_pool;
	int error = 0;
	unsigned int state = serv->sv_nrthreads-1;

	if (pool == NULL) {
		/* The -1 assumes caller has done a svc_get() */
		nrservs -= (serv->sv_nrthreads-1);
	} else {
		spin_lock_bh(&pool->sp_lock);
		nrservs -= pool->sp_nrthreads;
		spin_unlock_bh(&pool->sp_lock);
	}

	/* create new threads */
	while (nrservs > 0) {
		nrservs--;
		chosen_pool = choose_pool(serv, pool, &state);

		rqstp = svc_prepare_thread(serv, chosen_pool);
		if (IS_ERR(rqstp)) {
			error = PTR_ERR(rqstp);
			break;
		}

		__module_get(serv->sv_module);
		task = kthread_create(serv->sv_function, rqstp, serv->sv_name);
		if (IS_ERR(task)) {
			error = PTR_ERR(task);
			module_put(serv->sv_module);
			svc_exit_thread(rqstp);
			break;
		}

		rqstp->rq_task = task;
		if (serv->sv_nrpools > 1)
			svc_pool_map_set_cpumask(task, chosen_pool->sp_id);

		svc_sock_update_bufs(serv);
		wake_up_process(task);
	}
	/* destroy old threads */
	while (nrservs < 0 &&
	       (task = choose_victim(serv, pool, &state)) != NULL) {
		send_sig(SIGINT, task, 1);
		nrservs++;
	}

	return error;
}