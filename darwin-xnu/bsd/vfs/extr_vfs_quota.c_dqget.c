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
typedef  scalar_t__ u_int32_t ;
struct vnode {int dummy; } ;
struct timeval {scalar_t__ tv_sec; } ;
struct quotafile {scalar_t__ qf_btime; scalar_t__ qf_itime; struct vnode* qf_vp; } ;
struct TYPE_2__ {struct dquot* le_next; } ;
struct dquot {scalar_t__ dq_id; int dq_cnt; int dq_flags; int dq_type; scalar_t__ dq_isoftlimit; scalar_t__ dq_bsoftlimit; scalar_t__ dq_ihardlimit; scalar_t__ dq_bhardlimit; scalar_t__ dq_btime; scalar_t__ dq_itime; struct quotafile* dq_qfile; int /*<<< orphan*/  dq_index; int /*<<< orphan*/  dq_dqb; TYPE_1__ dq_hash; } ;
struct dqhash {struct dquot* lh_first; } ;

/* Variables and functions */
 struct dqhash* DQHASH (struct vnode*,scalar_t__) ; 
 scalar_t__ DQUOTINC ; 
 int DQ_FAKE ; 
 int DQ_MOD ; 
 int EINVAL ; 
 int EUSERS ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct dqhash*,struct dquot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct dquot*,int /*<<< orphan*/ ) ; 
 int MAXQUOTAS ; 
 int /*<<< orphan*/  M_DQUOT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct dquot* NODQUOT ; 
 struct vnode* NULLVP ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct dquot* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct dquot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct dquot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FREE (struct dquot*,int /*<<< orphan*/ ) ; 
 scalar_t__ _MALLOC (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int desireddquot ; 
 int desiredvnodes ; 
 int /*<<< orphan*/  dq_freelist ; 
 int /*<<< orphan*/  dq_hash ; 
 int dq_list_lock () ; 
 scalar_t__ dq_list_lock_changed (int) ; 
 int dq_list_lock_val () ; 
 int /*<<< orphan*/  dq_list_unlock () ; 
 int /*<<< orphan*/  dq_lock_internal (struct dquot*) ; 
 int /*<<< orphan*/  dq_unlock_internal (struct dquot*) ; 
 int /*<<< orphan*/  dqdirtylist ; 
 int /*<<< orphan*/  dqfreelist ; 
 int /*<<< orphan*/  dqisinitialized () ; 
 int dqlookup (struct quotafile*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dqrele (struct dquot*) ; 
 int /*<<< orphan*/  microtime (struct timeval*) ; 
 int numdquot ; 
 scalar_t__ qf_ref (struct quotafile*) ; 
 int /*<<< orphan*/  qf_rele (struct quotafile*) ; 
 int /*<<< orphan*/  tablefull (char*) ; 

int
dqget(u_int32_t id, struct quotafile *qfp, int type, struct dquot **dqp)
{
	struct dquot *dq;
	struct dquot *ndq = NULL;
	struct dquot *fdq = NULL;
	struct dqhash *dqh;
	struct vnode *dqvp;
	int error = 0;
	int listlockval = 0;

	if (!dqisinitialized()) {
		*dqp = NODQUOT;
		return (EINVAL);
	}

	if ( id == 0 || qfp->qf_vp == NULLVP ) {
		*dqp = NODQUOT;
		return (EINVAL);
	}
	dq_list_lock();

	if ( (qf_ref(qfp)) ) {
	        dq_list_unlock();

		*dqp = NODQUOT;
		return (EINVAL);
	}
	if ( (dqvp = qfp->qf_vp) == NULLVP ) {
	        qf_rele(qfp);
		dq_list_unlock();

		*dqp = NODQUOT;
		return (EINVAL);
	}
	dqh = DQHASH(dqvp, id);

relookup:
	listlockval = dq_list_lock_val();

	/*
	 * Check the cache first.
	 */
	for (dq = dqh->lh_first; dq; dq = dq->dq_hash.le_next) {
		if (dq->dq_id != id ||
		    dq->dq_qfile->qf_vp != dqvp)
			continue;

		dq_lock_internal(dq);
		if (dq_list_lock_changed(listlockval)) {
			dq_unlock_internal(dq);
			goto relookup;
		}

		/*
		 * dq_lock_internal may drop the quota_list_lock to msleep, so
		 * we need to re-evaluate the identity of this dq
		 */
		if (dq->dq_id != id || dq->dq_qfile == NULL ||
		    dq->dq_qfile->qf_vp != dqvp) {
		        dq_unlock_internal(dq);
			goto relookup;
		}
		/*
		 * Cache hit with no references.  Take
		 * the structure off the free list.
		 */
		if (dq->dq_cnt++ == 0) {
			if (dq->dq_flags & DQ_MOD)
				TAILQ_REMOVE(&dqdirtylist, dq, dq_freelist);
			else
				TAILQ_REMOVE(&dqfreelist, dq, dq_freelist);
		}
		dq_unlock_internal(dq);

		if (fdq != NULL) {
		        /*
			 * we grabbed this from the free list in the first pass
			 * but we found the dq we were looking for in
			 * the cache the 2nd time through
			 * so stick it back on the free list and return the cached entry
			 */
		        TAILQ_INSERT_HEAD(&dqfreelist, fdq, dq_freelist);
		}
		qf_rele(qfp);
	        dq_list_unlock();
		
		if (ndq != NULL) {
		        /*
			 * we allocated this in the first pass
			 * but we found the dq we were looking for in
			 * the cache the 2nd time through so free it
			 */
		        _FREE(ndq, M_DQUOT);
		}
		*dqp = dq;

		return (0);
	}
	/*
	 * Not in cache, allocate a new one.
	 */
	if (TAILQ_EMPTY(&dqfreelist) &&
	    numdquot < MAXQUOTAS * desiredvnodes)
		desireddquot += DQUOTINC;

	if (fdq != NULL) {
	        /*
		 * we captured this from the free list
		 * in the first pass through, so go
		 * ahead and use it
		 */
	        dq = fdq;
		fdq = NULL;
	} else if (numdquot < desireddquot) {
	        if (ndq == NULL) {
		        /*
			 * drop the quota list lock since MALLOC may block
			 */
		        dq_list_unlock();

			ndq = (struct dquot *)_MALLOC(sizeof *dq, M_DQUOT, M_WAITOK);
			bzero((char *)ndq, sizeof *dq);

		        listlockval = dq_list_lock();
			/*
			 * need to look for the entry again in the cache
			 * since we dropped the quota list lock and
			 * someone else may have beaten us to creating it
			 */
			goto relookup;
		} else {
		        /*
			 * we allocated this in the first pass through
			 * and we're still under out target, so go
			 * ahead and use it
			 */
		        dq = ndq;
			ndq = NULL;
			numdquot++;
		}
	} else {
	        if (TAILQ_EMPTY(&dqfreelist)) {
		        qf_rele(qfp);
		        dq_list_unlock();

			if (ndq) {
			        /*
				 * we allocated this in the first pass through
				 * but we're now at the limit of our cache size
				 * so free it
				 */
			        _FREE(ndq, M_DQUOT);
			}
			tablefull("dquot");
			*dqp = NODQUOT;
			return (EUSERS);
		}
		dq = TAILQ_FIRST(&dqfreelist);

		dq_lock_internal(dq);

		if (dq_list_lock_changed(listlockval) || dq->dq_cnt || (dq->dq_flags & DQ_MOD)) {
		        /*
			 * we lost the race while we weren't holding
			 * the quota list lock... dq_lock_internal
			 * will drop it to msleep... this dq has been
			 * reclaimed... go find another
			 */
		        dq_unlock_internal(dq);

			/*
			 * need to look for the entry again in the cache
			 * since we dropped the quota list lock and
			 * someone else may have beaten us to creating it
			 */
			goto relookup;
		}
		TAILQ_REMOVE(&dqfreelist, dq, dq_freelist);

		if (dq->dq_qfile != NULL) {
		        LIST_REMOVE(dq, dq_hash);
			dq->dq_qfile = NULL;
			dq->dq_id = 0;
		}
		dq_unlock_internal(dq);

		/*
		 * because we may have dropped the quota list lock
		 * in the call to dq_lock_internal, we need to 
		 * relookup in the hash in case someone else
		 * caused a dq with this identity to be created...
		 * if we don't find it, we'll use this one
		 */
		fdq = dq;
		goto relookup;
	}
	/*
	 * we've either freshly allocated a dq
	 * or we've atomically pulled it out of
	 * the hash and freelists... no one else
	 * can have a reference, which means no
	 * one else can be trying to use this dq
	 */
	dq_lock_internal(dq);
	if (dq_list_lock_changed(listlockval)) {
		dq_unlock_internal(dq);
		goto relookup;
	}

	/*
	 * Initialize the contents of the dquot structure.
	 */
	dq->dq_cnt = 1;
	dq->dq_flags = 0;
	dq->dq_id = id;
	dq->dq_qfile = qfp;
	dq->dq_type = type;
	/*
	 * once we insert it in the hash and
	 * drop the quota_list_lock, it can be
	 * 'found'... however, we're still holding
	 * the dq_lock which will keep us from doing
	 * anything with it until we've finished
	 * initializing it...
	 */
	LIST_INSERT_HEAD(dqh, dq, dq_hash);
	dq_list_unlock();

	if (ndq) {
	        /*
		 * we allocated this in the first pass through
		 * but we didn't need it, so free it after
		 * we've droped the quota list lock
		 */
	        _FREE(ndq, M_DQUOT);
	}

	error = dqlookup(qfp, id, &dq->dq_dqb, &dq->dq_index);

	/*
	 * I/O error in reading quota file, release
	 * quota structure and reflect problem to caller.
	 */
	if (error) {
	        dq_list_lock();

		dq->dq_id = 0;
		dq->dq_qfile = NULL;
		LIST_REMOVE(dq, dq_hash);

		dq_unlock_internal(dq);
		qf_rele(qfp);
	        dq_list_unlock();

		dqrele(dq);

		*dqp = NODQUOT;
		return (error);
	}
	/*
	 * Check for no limit to enforce.
	 * Initialize time values if necessary.
	 */
	if (dq->dq_isoftlimit == 0 && dq->dq_bsoftlimit == 0 &&
	    dq->dq_ihardlimit == 0 && dq->dq_bhardlimit == 0)
		dq->dq_flags |= DQ_FAKE;
	if (dq->dq_id != 0) {
		struct timeval tv;

		microtime(&tv);
		if (dq->dq_btime == 0)
			dq->dq_btime = tv.tv_sec + qfp->qf_btime;
		if (dq->dq_itime == 0)
			dq->dq_itime = tv.tv_sec + qfp->qf_itime;
	}
	dq_list_lock();
	dq_unlock_internal(dq);
	qf_rele(qfp);
	dq_list_unlock();

	*dqp = dq;
	return (0);
}