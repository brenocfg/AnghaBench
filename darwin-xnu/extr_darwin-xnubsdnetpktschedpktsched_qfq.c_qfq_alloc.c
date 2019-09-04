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
struct qfq_if {int qif_maxclasses; int /*<<< orphan*/ * qif_groups; int /*<<< orphan*/ * qif_class_tbl; int /*<<< orphan*/  qif_maxslots; int /*<<< orphan*/ * qif_ifq; } ;
struct qfq_group {int dummy; } ;
struct qfq_class {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int IFCQ_SC_MAX ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int QFQ_MAX_INDEX ; 
 int /*<<< orphan*/  QFQ_MAX_SLOTS ; 
 int /*<<< orphan*/  _FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (struct qfq_if*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pktsched_verbose ; 
 int /*<<< orphan*/  qfq_size ; 
 int /*<<< orphan*/  qfq_style (struct qfq_if*) ; 
 int /*<<< orphan*/  qfq_zone ; 
 struct qfq_if* zalloc (int /*<<< orphan*/ ) ; 
 struct qfq_if* zalloc_noblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct qfq_if*) ; 

struct qfq_if *
qfq_alloc(struct ifnet *ifp, int how)
{
	struct qfq_if	*qif;

	qif = (how == M_WAITOK) ? zalloc(qfq_zone) : zalloc_noblock(qfq_zone);
	if (qif == NULL)
		return (NULL);

	bzero(qif, qfq_size);
	qif->qif_ifq = &ifp->if_snd;

	qif->qif_maxclasses = IFCQ_SC_MAX;
	/*
	 * TODO: adi@apple.com
	 *
	 * Ideally I would like to have the following
	 * but QFQ needs further modifications.
	 *
	 *	qif->qif_maxslots = IFCQ_SC_MAX;
	 */
	qif->qif_maxslots = QFQ_MAX_SLOTS;

	if ((qif->qif_class_tbl = _MALLOC(sizeof (struct qfq_class *) *
	    qif->qif_maxclasses, M_DEVBUF, M_WAITOK|M_ZERO)) == NULL) {
		log(LOG_ERR, "%s: %s unable to allocate class table array\n",
		    if_name(ifp), qfq_style(qif));
		goto error;
	}

	if ((qif->qif_groups = _MALLOC(sizeof (struct qfq_group *) *
	    (QFQ_MAX_INDEX + 1), M_DEVBUF, M_WAITOK|M_ZERO)) == NULL) {
		log(LOG_ERR, "%s: %s unable to allocate group array\n",
		    if_name(ifp), qfq_style(qif));
		goto error;
	}

	if (pktsched_verbose) {
		log(LOG_DEBUG, "%s: %s scheduler allocated\n",
		    if_name(ifp), qfq_style(qif));
	}

	return (qif);

error:
	if (qif->qif_class_tbl != NULL) {
		_FREE(qif->qif_class_tbl, M_DEVBUF);
		qif->qif_class_tbl = NULL;
	}
	if (qif->qif_groups != NULL) {
		_FREE(qif->qif_groups, M_DEVBUF);
		qif->qif_groups = NULL;
	}
	zfree(qfq_zone, qif);

	return (NULL);
}