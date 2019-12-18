#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  provname ;
struct TYPE_13__ {scalar_t__ p_pid; int p_lflag; int /*<<< orphan*/  p_dtrace_probes; } ;
typedef  TYPE_1__ proc_t ;
typedef  scalar_t__ pid_t ;
typedef  scalar_t__ fasttrap_provider_type_t ;
struct TYPE_14__ {scalar_t__ ftp_pid; scalar_t__ ftp_provider_type; int /*<<< orphan*/  ftp_mtx; struct TYPE_14__* ftp_next; int /*<<< orphan*/  ftp_provid; int /*<<< orphan*/  ftp_name; int /*<<< orphan*/  ftp_retired; int /*<<< orphan*/ * ftp_proc; int /*<<< orphan*/  ftp_cmtx; } ;
typedef  TYPE_2__ fasttrap_provider_t ;
struct TYPE_15__ {int /*<<< orphan*/  ftb_mtx; TYPE_2__* ftb_data; } ;
typedef  TYPE_3__ fasttrap_bucket_t ;
typedef  int /*<<< orphan*/  dtrace_pattr_t ;
typedef  int /*<<< orphan*/  cred_t ;
struct TYPE_16__ {TYPE_3__* fth_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DTRACE_PRIV_OWNER ; 
 int DTRACE_PRIV_PROC ; 
 int DTRACE_PRIV_ZONEOWNER ; 
 int DTRACE_PROVNAMELEN ; 
 size_t FASTTRAP_PROVS_INDEX (scalar_t__,char const*) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int P_LEXIT ; 
 int P_LINVFORK ; 
 scalar_t__ dtrace_register (char*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fasttrap_lck_attr ; 
 int /*<<< orphan*/  fasttrap_lck_grp ; 
 int /*<<< orphan*/ * fasttrap_proc_lookup (scalar_t__) ; 
 int /*<<< orphan*/  fasttrap_provider_free (TYPE_2__*) ; 
 TYPE_8__ fasttrap_provs ; 
 int /*<<< orphan*/ * kauth_cred_proc_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ **) ; 
 TYPE_2__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const pid_attr ; 
 int /*<<< orphan*/  pid_pops ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 
 int snprintf (char*,int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  usdt_pops ; 

__attribute__((used)) static fasttrap_provider_t *
fasttrap_provider_lookup(proc_t *p, fasttrap_provider_type_t provider_type, const char *name,
    const dtrace_pattr_t *pattr)
{
	pid_t pid = p->p_pid;
	fasttrap_provider_t *fp, *new_fp = NULL;
	fasttrap_bucket_t *bucket;
	char provname[DTRACE_PROVNAMELEN];
	cred_t *cred;

	ASSERT(strlen(name) < sizeof (fp->ftp_name));
	ASSERT(pattr != NULL);

	bucket = &fasttrap_provs.fth_table[FASTTRAP_PROVS_INDEX(pid, name)];
	lck_mtx_lock(&bucket->ftb_mtx);

	/*
	 * Take a lap through the list and return the match if we find it.
	 */
	for (fp = bucket->ftb_data; fp != NULL; fp = fp->ftp_next) {
		if (fp->ftp_pid == pid &&
		    fp->ftp_provider_type == provider_type &&
		    strncmp(fp->ftp_name, name, sizeof(fp->ftp_name)) == 0 &&
		    !fp->ftp_retired) {
			lck_mtx_lock(&fp->ftp_mtx);
			lck_mtx_unlock(&bucket->ftb_mtx);
			return (fp);
		}
	}

	/*
	 * Drop the bucket lock so we don't try to perform a sleeping
	 * allocation under it.
	 */
	lck_mtx_unlock(&bucket->ftb_mtx);

	/*
	 * Make sure the process isn't a child created as the result
	 * of a vfork(2), and isn't a zombie (but may be in fork).
	 */
	proc_lock(p);
	if (p->p_lflag & (P_LINVFORK | P_LEXIT)) {
		proc_unlock(p);
		return (NULL);
	}

	/*
	 * Increment p_dtrace_probes so that the process knows to inform us
	 * when it exits or execs. fasttrap_provider_free() decrements this
	 * when we're done with this provider.
	 */
	p->p_dtrace_probes++;

	/*
	 * Grab the credentials for this process so we have
	 * something to pass to dtrace_register().
	 * APPLE NOTE:  We have no equivalent to crhold,
	 * even though there is a cr_ref filed in ucred.
	 */
	cred = kauth_cred_proc_ref(p);
	proc_unlock(p);

	new_fp = kmem_zalloc(sizeof (fasttrap_provider_t), KM_SLEEP);
	ASSERT(new_fp != NULL);
	new_fp->ftp_pid = p->p_pid;
	new_fp->ftp_proc = fasttrap_proc_lookup(pid);
	new_fp->ftp_provider_type = provider_type;

	/*
	 * APPLE NOTE:  locks require explicit init
	 */
	lck_mtx_init(&new_fp->ftp_mtx, fasttrap_lck_grp, fasttrap_lck_attr);
	lck_mtx_init(&new_fp->ftp_cmtx, fasttrap_lck_grp, fasttrap_lck_attr);

	ASSERT(new_fp->ftp_proc != NULL);

	lck_mtx_lock(&bucket->ftb_mtx);

	/*
	 * Take another lap through the list to make sure a provider hasn't
	 * been created for this pid while we weren't under the bucket lock.
	 */
	for (fp = bucket->ftb_data; fp != NULL; fp = fp->ftp_next) {
		if (fp->ftp_pid == pid && strncmp(fp->ftp_name, name, sizeof(fp->ftp_name)) == 0 &&
		    !fp->ftp_retired) {
			lck_mtx_lock(&fp->ftp_mtx);
			lck_mtx_unlock(&bucket->ftb_mtx);
			fasttrap_provider_free(new_fp);
			kauth_cred_unref(&cred);
			return (fp);
		}
	}

	(void) strlcpy(new_fp->ftp_name, name, sizeof(new_fp->ftp_name));

	/*
	 * Fail and return NULL if either the provider name is too long
	 * or we fail to register this new provider with the DTrace
	 * framework. Note that this is the only place we ever construct
	 * the full provider name -- we keep it in pieces in the provider
	 * structure.
	 */
	if (snprintf(provname, sizeof (provname), "%s%u", name, (uint_t)pid) >=
	    (int)sizeof (provname) ||
	    dtrace_register(provname, pattr,
	    DTRACE_PRIV_PROC | DTRACE_PRIV_OWNER | DTRACE_PRIV_ZONEOWNER, cred,
	    pattr == &pid_attr ? &pid_pops : &usdt_pops, new_fp,
	    &new_fp->ftp_provid) != 0) {
		lck_mtx_unlock(&bucket->ftb_mtx);
		fasttrap_provider_free(new_fp);
		kauth_cred_unref(&cred);
		return (NULL);
	}

	new_fp->ftp_next = bucket->ftb_data;
	bucket->ftb_data = new_fp;

	lck_mtx_lock(&new_fp->ftp_mtx);
	lck_mtx_unlock(&bucket->ftb_mtx);

	kauth_cred_unref(&cred);

	return (new_fp);
}