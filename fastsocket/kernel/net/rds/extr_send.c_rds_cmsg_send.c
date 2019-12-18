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
struct rds_sock {int dummy; } ;
struct rds_message {int dummy; } ;
struct msghdr {int dummy; } ;
struct cmsghdr {scalar_t__ cmsg_level; int cmsg_type; } ;

/* Variables and functions */
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 int /*<<< orphan*/  CMSG_OK (struct msghdr*,struct cmsghdr*) ; 
 int EINVAL ; 
#define  RDS_CMSG_ATOMIC_CSWP 134 
#define  RDS_CMSG_ATOMIC_FADD 133 
#define  RDS_CMSG_MASKED_ATOMIC_CSWP 132 
#define  RDS_CMSG_MASKED_ATOMIC_FADD 131 
#define  RDS_CMSG_RDMA_ARGS 130 
#define  RDS_CMSG_RDMA_DEST 129 
#define  RDS_CMSG_RDMA_MAP 128 
 scalar_t__ SOL_RDS ; 
 int rds_cmsg_atomic (struct rds_sock*,struct rds_message*,struct cmsghdr*) ; 
 int rds_cmsg_rdma_args (struct rds_sock*,struct rds_message*,struct cmsghdr*) ; 
 int rds_cmsg_rdma_dest (struct rds_sock*,struct rds_message*,struct cmsghdr*) ; 
 int rds_cmsg_rdma_map (struct rds_sock*,struct rds_message*,struct cmsghdr*) ; 

__attribute__((used)) static int rds_cmsg_send(struct rds_sock *rs, struct rds_message *rm,
			 struct msghdr *msg, int *allocated_mr)
{
	struct cmsghdr *cmsg;
	int ret = 0;

	for (cmsg = CMSG_FIRSTHDR(msg); cmsg; cmsg = CMSG_NXTHDR(msg, cmsg)) {
		if (!CMSG_OK(msg, cmsg))
			return -EINVAL;

		if (cmsg->cmsg_level != SOL_RDS)
			continue;

		/* As a side effect, RDMA_DEST and RDMA_MAP will set
		 * rm->rdma.m_rdma_cookie and rm->rdma.m_rdma_mr.
		 */
		switch (cmsg->cmsg_type) {
		case RDS_CMSG_RDMA_ARGS:
			ret = rds_cmsg_rdma_args(rs, rm, cmsg);
			break;

		case RDS_CMSG_RDMA_DEST:
			ret = rds_cmsg_rdma_dest(rs, rm, cmsg);
			break;

		case RDS_CMSG_RDMA_MAP:
			ret = rds_cmsg_rdma_map(rs, rm, cmsg);
			if (!ret)
				*allocated_mr = 1;
			break;
		case RDS_CMSG_ATOMIC_CSWP:
		case RDS_CMSG_ATOMIC_FADD:
		case RDS_CMSG_MASKED_ATOMIC_CSWP:
		case RDS_CMSG_MASKED_ATOMIC_FADD:
			ret = rds_cmsg_atomic(rs, rm, cmsg);
			break;

		default:
			return -EINVAL;
		}

		if (ret)
			break;
	}

	return ret;
}