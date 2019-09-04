#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ftp_ccount; scalar_t__ ftp_mcount; scalar_t__ ftp_rcount; struct TYPE_5__* ftp_next; scalar_t__ ftp_marked; int /*<<< orphan*/  ftp_provid; int /*<<< orphan*/  ftp_mtx; int /*<<< orphan*/  ftp_retired; } ;
typedef  TYPE_1__ fasttrap_provider_t ;
struct TYPE_6__ {int /*<<< orphan*/  ftb_mtx; int /*<<< orphan*/  ftb_data; } ;
typedef  TYPE_2__ fasttrap_bucket_t ;
typedef  int /*<<< orphan*/  dtrace_provider_id_t ;
struct TYPE_7__ {unsigned int fth_nent; TYPE_2__* fth_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  dtrace_condense (int /*<<< orphan*/ ) ; 
 scalar_t__ dtrace_unregister (int /*<<< orphan*/ ) ; 
 int fasttrap_max ; 
 int /*<<< orphan*/  fasttrap_provider_free (TYPE_1__*) ; 
 TYPE_3__ fasttrap_provs ; 
 int fasttrap_total ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int
fasttrap_pid_cleanup_providers(void)
{
	fasttrap_provider_t **fpp, *fp;
	fasttrap_bucket_t *bucket;
	dtrace_provider_id_t provid;
	unsigned int later = 0, i;

	/*
	 * Iterate over all the providers trying to remove the marked
	 * ones. If a provider is marked but not retired, we just
	 * have to take a crack at removing it -- it's no big deal if
	 * we can't.
	 */
	for (i = 0; i < fasttrap_provs.fth_nent; i++) {
		bucket = &fasttrap_provs.fth_table[i];
		lck_mtx_lock(&bucket->ftb_mtx);
		fpp = (fasttrap_provider_t **)&bucket->ftb_data;

		while ((fp = *fpp) != NULL) {
			if (!fp->ftp_marked) {
				fpp = &fp->ftp_next;
				continue;
			}

			lck_mtx_lock(&fp->ftp_mtx);

			/*
			 * If this provider has consumers actively
			 * creating probes (ftp_ccount) or is a USDT
			 * provider (ftp_mcount), we can't unregister
			 * or even condense.
			 */
			if (fp->ftp_ccount != 0 ||
			    fp->ftp_mcount != 0) {
				fp->ftp_marked = 0;
				lck_mtx_unlock(&fp->ftp_mtx);
				continue;
			}

			if (!fp->ftp_retired || fp->ftp_rcount != 0)
				fp->ftp_marked = 0;

			lck_mtx_unlock(&fp->ftp_mtx);

			/*
			 * If we successfully unregister this
			 * provider we can remove it from the hash
			 * chain and free the memory. If our attempt
			 * to unregister fails and this is a retired
			 * provider, increment our flag to try again
			 * pretty soon. If we've consumed more than
			 * half of our total permitted number of
			 * probes call dtrace_condense() to try to
			 * clean out the unenabled probes.
			 */
			provid = fp->ftp_provid;
			if (dtrace_unregister(provid) != 0) {
				if (fasttrap_total > fasttrap_max / 2)
					(void) dtrace_condense(provid);
				later += fp->ftp_marked;
				fpp = &fp->ftp_next;
			} else {
				*fpp = fp->ftp_next;
				fasttrap_provider_free(fp);
			}
		}
		lck_mtx_unlock(&bucket->ftb_mtx);
	}

	return later;
}