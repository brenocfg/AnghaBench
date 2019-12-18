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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u16 ;
struct ipath_qp {int dummy; } ;
struct ipath_mcast_qp {int dummy; } ;
struct ipath_mcast {int dummy; } ;
struct ipath_ibdev {int dummy; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;

/* Variables and functions */
#define  EEXIST 130 
 int EINVAL ; 
#define  ENOMEM 129 
#define  ESRCH 128 
 int ipath_mcast_add (struct ipath_ibdev*,struct ipath_mcast*,struct ipath_mcast_qp*) ; 
 struct ipath_mcast* ipath_mcast_alloc (union ib_gid*) ; 
 int /*<<< orphan*/  ipath_mcast_free (struct ipath_mcast*) ; 
 struct ipath_mcast_qp* ipath_mcast_qp_alloc (struct ipath_qp*) ; 
 int /*<<< orphan*/  ipath_mcast_qp_free (struct ipath_mcast_qp*) ; 
 struct ipath_ibdev* to_idev (int /*<<< orphan*/ ) ; 
 struct ipath_qp* to_iqp (struct ib_qp*) ; 

int ipath_multicast_attach(struct ib_qp *ibqp, union ib_gid *gid, u16 lid)
{
	struct ipath_qp *qp = to_iqp(ibqp);
	struct ipath_ibdev *dev = to_idev(ibqp->device);
	struct ipath_mcast *mcast;
	struct ipath_mcast_qp *mqp;
	int ret;

	/*
	 * Allocate data structures since its better to do this outside of
	 * spin locks and it will most likely be needed.
	 */
	mcast = ipath_mcast_alloc(gid);
	if (mcast == NULL) {
		ret = -ENOMEM;
		goto bail;
	}
	mqp = ipath_mcast_qp_alloc(qp);
	if (mqp == NULL) {
		ipath_mcast_free(mcast);
		ret = -ENOMEM;
		goto bail;
	}
	switch (ipath_mcast_add(dev, mcast, mqp)) {
	case ESRCH:
		/* Neither was used: can't attach the same QP twice. */
		ipath_mcast_qp_free(mqp);
		ipath_mcast_free(mcast);
		ret = -EINVAL;
		goto bail;
	case EEXIST:		/* The mcast wasn't used */
		ipath_mcast_free(mcast);
		break;
	case ENOMEM:
		/* Exceeded the maximum number of mcast groups. */
		ipath_mcast_qp_free(mqp);
		ipath_mcast_free(mcast);
		ret = -ENOMEM;
		goto bail;
	default:
		break;
	}

	ret = 0;

bail:
	return ret;
}