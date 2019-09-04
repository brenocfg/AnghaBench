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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int u_int32_t ;
struct ifclassq {int /*<<< orphan*/  ifcq_type; int /*<<< orphan*/  ifcq_dropcnt; int /*<<< orphan*/  ifcq_xmitcnt; } ;
struct if_ifclassq_stats {int /*<<< orphan*/  ifqs_scheduler; int /*<<< orphan*/  ifqs_dropcnt; int /*<<< orphan*/  ifqs_xmitcnt; int /*<<< orphan*/  ifqs_maxlen; int /*<<< orphan*/  ifqs_len; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  IFCQ_IS_READY (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_LEN (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_LOCK (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_MAXLEN (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_UNLOCK (struct ifclassq*) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  _FREE (struct if_ifclassq_stats*,int /*<<< orphan*/ ) ; 
 struct if_ifclassq_stats* _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pktsched_getqstats (struct ifclassq*,int,struct if_ifclassq_stats*) ; 

int
ifclassq_getqstats(struct ifclassq *ifq, u_int32_t qid, void *ubuf,
    u_int32_t *nbytes)
{
	struct if_ifclassq_stats *ifqs;
	int err;

	if (*nbytes < sizeof (*ifqs))
		return (EINVAL);

	ifqs = _MALLOC(sizeof (*ifqs), M_TEMP, M_WAITOK | M_ZERO);
	if (ifqs == NULL)
		return (ENOMEM);

	IFCQ_LOCK(ifq);
	if (!IFCQ_IS_READY(ifq)) {
		IFCQ_UNLOCK(ifq);
		_FREE(ifqs, M_TEMP);
		return (ENXIO);
	}

	ifqs->ifqs_len = IFCQ_LEN(ifq);
	ifqs->ifqs_maxlen = IFCQ_MAXLEN(ifq);
	*(&ifqs->ifqs_xmitcnt) = *(&ifq->ifcq_xmitcnt);
	*(&ifqs->ifqs_dropcnt) = *(&ifq->ifcq_dropcnt);
	ifqs->ifqs_scheduler = ifq->ifcq_type;

	err = pktsched_getqstats(ifq, qid, ifqs);
	IFCQ_UNLOCK(ifq);

	if (err == 0 && (err = copyout((caddr_t)ifqs,
	    (user_addr_t)(uintptr_t)ubuf, sizeof (*ifqs))) == 0)
		*nbytes = sizeof (*ifqs);

	_FREE(ifqs, M_TEMP);

	return (err);
}