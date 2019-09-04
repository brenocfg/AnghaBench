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
struct ifclassq {int dummy; } ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/  classq_pkt_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_ENQUEUE (struct ifclassq*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFCQ_LOCK (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_LOCK_SPIN (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_UNLOCK (struct ifclassq*) ; 
#define  QP_MBUF 128 

errno_t
ifclassq_enqueue(struct ifclassq *ifq, void *p, classq_pkt_type_t ptype,
    boolean_t *pdrop)
{
	errno_t err;

	switch (ptype) {
	case QP_MBUF:
		IFCQ_LOCK_SPIN(ifq);
		break;

	default:
		IFCQ_LOCK(ifq);
		break;
	}

	IFCQ_ENQUEUE(ifq, p, ptype, err, pdrop);
	IFCQ_UNLOCK(ifq);
	return (err);
}