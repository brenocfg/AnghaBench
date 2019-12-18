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
struct svc_serv {int /*<<< orphan*/  sv_max_mesg; int /*<<< orphan*/  sv_xdrsize; int /*<<< orphan*/  sv_nrthreads; } ;
struct svc_rqst {void* rq_resp; void* rq_argp; struct svc_pool* rq_pool; struct svc_serv* rq_server; int /*<<< orphan*/  rq_all; int /*<<< orphan*/  rq_wait; } ;
struct svc_pool {int /*<<< orphan*/  sp_lock; int /*<<< orphan*/  sp_all_threads; int /*<<< orphan*/  sp_nrthreads; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct svc_rqst* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct svc_rqst* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_exit_thread (struct svc_rqst*) ; 
 int /*<<< orphan*/  svc_init_buffer (struct svc_rqst*,int /*<<< orphan*/ ) ; 

struct svc_rqst *
svc_prepare_thread(struct svc_serv *serv, struct svc_pool *pool)
{
	struct svc_rqst	*rqstp;

	rqstp = kzalloc(sizeof(*rqstp), GFP_KERNEL);
	if (!rqstp)
		goto out_enomem;

	init_waitqueue_head(&rqstp->rq_wait);

	serv->sv_nrthreads++;
	spin_lock_bh(&pool->sp_lock);
	pool->sp_nrthreads++;
	list_add(&rqstp->rq_all, &pool->sp_all_threads);
	spin_unlock_bh(&pool->sp_lock);
	rqstp->rq_server = serv;
	rqstp->rq_pool = pool;

	rqstp->rq_argp = kmalloc(serv->sv_xdrsize, GFP_KERNEL);
	if (!rqstp->rq_argp)
		goto out_thread;

	rqstp->rq_resp = kmalloc(serv->sv_xdrsize, GFP_KERNEL);
	if (!rqstp->rq_resp)
		goto out_thread;

	if (!svc_init_buffer(rqstp, serv->sv_max_mesg))
		goto out_thread;

	return rqstp;
out_thread:
	svc_exit_thread(rqstp);
out_enomem:
	return ERR_PTR(-ENOMEM);
}