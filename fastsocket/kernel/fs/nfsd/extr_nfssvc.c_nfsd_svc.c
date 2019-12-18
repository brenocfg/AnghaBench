#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sv_nrthreads; } ;

/* Variables and functions */
 int NFSD_MAXSERVS ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nfsd_create_serv () ; 
 int /*<<< orphan*/  nfsd_mutex ; 
 TYPE_1__* nfsd_serv ; 
 int /*<<< orphan*/  nfsd_shutdown () ; 
 int nfsd_startup (unsigned short,int) ; 
 int nfsd_up ; 
 int /*<<< orphan*/  svc_destroy (TYPE_1__*) ; 
 int svc_set_num_threads (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

int
nfsd_svc(unsigned short port, int nrservs)
{
	int	error;
	bool	nfsd_up_before;

	mutex_lock(&nfsd_mutex);
	dprintk("nfsd: creating service\n");
	if (nrservs <= 0)
		nrservs = 0;
	if (nrservs > NFSD_MAXSERVS)
		nrservs = NFSD_MAXSERVS;
	error = 0;
	if (nrservs == 0 && nfsd_serv == NULL)
		goto out;

	error = nfsd_create_serv();
	if (error)
		goto out;

	nfsd_up_before = nfsd_up;

	error = nfsd_startup(port, nrservs);
	if (error)
		goto out_destroy;
	error = svc_set_num_threads(nfsd_serv, NULL, nrservs);
	if (error)
		goto out_shutdown;
	/* We are holding a reference to nfsd_serv which
	 * we don't want to count in the return value,
	 * so subtract 1
	 */
	error = nfsd_serv->sv_nrthreads - 1;
out_shutdown:
	if (error < 0 && !nfsd_up_before)
		nfsd_shutdown();
out_destroy:
	svc_destroy(nfsd_serv);		/* Release server */
out:
	mutex_unlock(&nfsd_mutex);
	return error;
}