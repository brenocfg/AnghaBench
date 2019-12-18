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
struct net {int dummy; } ;
struct msghdr {int dummy; } ;
struct ipcm_cookie {int /*<<< orphan*/  addr; int /*<<< orphan*/  oif; int /*<<< orphan*/  opt; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct in_pktinfo {TYPE_1__ ipi_spec_dst; int /*<<< orphan*/  ipi_ifindex; } ;
struct cmsghdr {scalar_t__ cmsg_level; int cmsg_type; int cmsg_len; } ;

/* Variables and functions */
 int CMSG_ALIGN (int) ; 
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 int CMSG_LEN (int) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 int /*<<< orphan*/  CMSG_OK (struct msghdr*,struct cmsghdr*) ; 
 int EINVAL ; 
#define  IP_PKTINFO 129 
#define  IP_RETOPTS 128 
 scalar_t__ SOL_IP ; 
 int ip_options_get (struct net*,int /*<<< orphan*/ *,scalar_t__,int) ; 

int ip_cmsg_send(struct net *net, struct msghdr *msg, struct ipcm_cookie *ipc)
{
	int err;
	struct cmsghdr *cmsg;

	for (cmsg = CMSG_FIRSTHDR(msg); cmsg; cmsg = CMSG_NXTHDR(msg, cmsg)) {
		if (!CMSG_OK(msg, cmsg))
			return -EINVAL;
		if (cmsg->cmsg_level != SOL_IP)
			continue;
		switch (cmsg->cmsg_type) {
		case IP_RETOPTS:
			err = cmsg->cmsg_len - CMSG_ALIGN(sizeof(struct cmsghdr));
			err = ip_options_get(net, &ipc->opt, CMSG_DATA(cmsg),
					     err < 40 ? err : 40);
			if (err)
				return err;
			break;
		case IP_PKTINFO:
		{
			struct in_pktinfo *info;
			if (cmsg->cmsg_len != CMSG_LEN(sizeof(struct in_pktinfo)))
				return -EINVAL;
			info = (struct in_pktinfo *)CMSG_DATA(cmsg);
			ipc->oif = info->ipi_ifindex;
			ipc->addr = info->ipi_spec_dst.s_addr;
			break;
		}
		default:
			return -EINVAL;
		}
	}
	return 0;
}