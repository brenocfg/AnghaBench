#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_5__ {TYPE_1__ addr; } ;
struct svc_rqst {TYPE_2__ rq_daddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct in_pktinfo {TYPE_3__ ipi_spec_dst; } ;
struct cmsghdr {scalar_t__ cmsg_type; } ;

/* Variables and functions */
 struct in_pktinfo* CMSG_DATA (struct cmsghdr*) ; 
 scalar_t__ IP_PKTINFO ; 

__attribute__((used)) static int svc_udp_get_dest_address4(struct svc_rqst *rqstp,
				     struct cmsghdr *cmh)
{
	struct in_pktinfo *pki = CMSG_DATA(cmh);
	if (cmh->cmsg_type != IP_PKTINFO)
		return 0;
	rqstp->rq_daddr.addr.s_addr = pki->ipi_spec_dst.s_addr;
	return 1;
}