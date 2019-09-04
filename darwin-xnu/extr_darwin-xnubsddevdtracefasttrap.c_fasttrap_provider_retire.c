#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ p_pid; } ;
typedef  TYPE_2__ proc_t ;
struct TYPE_9__ {scalar_t__ ftp_pid; int ftp_retired; scalar_t__ ftp_mcount; int ftp_marked; int /*<<< orphan*/  ftp_mtx; int /*<<< orphan*/  ftp_provid; scalar_t__ ftp_pcount; TYPE_1__* ftp_proc; int /*<<< orphan*/  ftp_name; struct TYPE_9__* ftp_next; } ;
typedef  TYPE_3__ fasttrap_provider_t ;
struct TYPE_10__ {int /*<<< orphan*/  ftb_mtx; TYPE_3__* ftb_data; } ;
typedef  TYPE_4__ fasttrap_bucket_t ;
typedef  int /*<<< orphan*/  dtrace_provider_id_t ;
struct TYPE_11__ {TYPE_4__* fth_table; } ;
struct TYPE_7__ {scalar_t__ ftpc_acount; scalar_t__ ftpc_rcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FASTTRAP_CLEANUP_PROVIDER ; 
 size_t FASTTRAP_PROVS_INDEX (scalar_t__,char const*) ; 
 int /*<<< orphan*/  atomic_add_32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  atomic_add_64 (scalar_t__*,int) ; 
 int /*<<< orphan*/  dtrace_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fasttrap_pid_cleanup (int /*<<< orphan*/ ) ; 
 TYPE_5__ fasttrap_provs ; 
 int /*<<< orphan*/  fasttrap_retired ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
fasttrap_provider_retire(proc_t *p, const char *name, int mprov)
{
	fasttrap_provider_t *fp;
	fasttrap_bucket_t *bucket;
	dtrace_provider_id_t provid;
	ASSERT(strlen(name) < sizeof (fp->ftp_name));

	bucket = &fasttrap_provs.fth_table[FASTTRAP_PROVS_INDEX(p->p_pid, name)];
	lck_mtx_lock(&bucket->ftb_mtx);

	for (fp = bucket->ftb_data; fp != NULL; fp = fp->ftp_next) {
		if (fp->ftp_pid == p->p_pid && strncmp(fp->ftp_name, name, sizeof(fp->ftp_name)) == 0 &&
		    !fp->ftp_retired)
			break;
	}

	if (fp == NULL) {
		lck_mtx_unlock(&bucket->ftb_mtx);
		return;
	}

	lck_mtx_lock(&fp->ftp_mtx);
	ASSERT(!mprov || fp->ftp_mcount > 0);
	if (mprov && --fp->ftp_mcount != 0)  {
		lck_mtx_unlock(&fp->ftp_mtx);
		lck_mtx_unlock(&bucket->ftb_mtx);
		return;
	}

	/*
	 * Mark the provider to be removed in our post-processing step, mark it
	 * retired, and drop the active count on its proc. Marking it indicates
	 * that we should try to remove it; setting the retired flag indicates
	 * that we're done with this provider; dropping the active the proc
	 * releases our hold, and when this reaches zero (as it will during
	 * exit or exec) the proc and associated providers become defunct.
	 *
	 * We obviously need to take the bucket lock before the provider lock
	 * to perform the lookup, but we need to drop the provider lock
	 * before calling into the DTrace framework since we acquire the
	 * provider lock in callbacks invoked from the DTrace framework. The
	 * bucket lock therefore protects the integrity of the provider hash
	 * table.
	 */
	atomic_add_64(&fp->ftp_proc->ftpc_acount, -1);
	ASSERT(fp->ftp_proc->ftpc_acount < fp->ftp_proc->ftpc_rcount);

	/*
	 * Add this provider probes to the retired count and
	 * make sure we don't add them twice
	 */
	atomic_add_32(&fasttrap_retired, fp->ftp_pcount);
	fp->ftp_pcount = 0;

	fp->ftp_retired = 1;
	fp->ftp_marked = 1;
	provid = fp->ftp_provid;
	lck_mtx_unlock(&fp->ftp_mtx);

	/*
	 * We don't have to worry about invalidating the same provider twice
	 * since fasttrap_provider_lookup() will ignore providers that have
	 * been marked as retired.
	 */
	dtrace_invalidate(provid);

	lck_mtx_unlock(&bucket->ftb_mtx);

	fasttrap_pid_cleanup(FASTTRAP_CLEANUP_PROVIDER);
}