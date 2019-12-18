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
struct svc_serv {scalar_t__ sv_nrthreads; struct svc_serv* sv_pools; int /*<<< orphan*/  (* sv_shutdown ) (struct svc_serv*) ;int /*<<< orphan*/  sv_temptimer; TYPE_1__* sv_program; } ;
struct TYPE_2__ {int /*<<< orphan*/  pg_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_clean_deferred (struct svc_serv*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct svc_serv*) ; 
 int /*<<< orphan*/  printk (char*,struct svc_serv*) ; 
 int /*<<< orphan*/  stub1 (struct svc_serv*) ; 
 int /*<<< orphan*/  svc_close_all (struct svc_serv*) ; 
 int /*<<< orphan*/  svc_pool_map_put () ; 
 scalar_t__ svc_serv_is_pooled (struct svc_serv*) ; 
 int /*<<< orphan*/  svc_sock_update_bufs (struct svc_serv*) ; 

void
svc_destroy(struct svc_serv *serv)
{
	dprintk("svc: svc_destroy(%s, %d)\n",
				serv->sv_program->pg_name,
				serv->sv_nrthreads);

	if (serv->sv_nrthreads) {
		if (--(serv->sv_nrthreads) != 0) {
			svc_sock_update_bufs(serv);
			return;
		}
	} else
		printk("svc_destroy: no threads for serv=%p!\n", serv);

	del_timer_sync(&serv->sv_temptimer);
	/*
	 * The set of xprts (contained in the sv_tempsocks and
	 * sv_permsocks lists) is now constant, since it is modified
	 * only by accepting new sockets (done by service threads in
	 * svc_recv) or aging old ones (done by sv_temptimer), or
	 * configuration changes (excluded by whatever locking the
	 * caller is using--nfsd_mutex in the case of nfsd).  So it's
	 * safe to traverse those lists and shut everything down:
	 */
	svc_close_all(serv);

	if (serv->sv_shutdown)
		serv->sv_shutdown(serv);

	cache_clean_deferred(serv);

	if (svc_serv_is_pooled(serv))
		svc_pool_map_put();

	kfree(serv->sv_pools);
	kfree(serv);
}