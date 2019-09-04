#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rtattr {int rta_type; } ;
struct nlmsghdr {scalar_t__ nlmsg_type; } ;
struct ifinfomsg {size_t ifi_index; int /*<<< orphan*/  ifi_type; int /*<<< orphan*/  ifi_flags; } ;
struct TYPE_5__ {struct TYPE_5__* ifa_next; void* ifa_name; int /*<<< orphan*/  ifa_netmask; int /*<<< orphan*/ * ifa_addr; int /*<<< orphan*/ * ifa_dstaddr; int /*<<< orphan*/ * ifa_broadaddr; int /*<<< orphan*/  ifa_flags; void* ifa_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  sa; } ;
struct ifaddrs_storage {size_t index; TYPE_1__ ifa; int /*<<< orphan*/  netmask; void* name; TYPE_2__ addr; TYPE_2__ ifu; struct ifaddrs_storage* hash_next; } ;
struct ifaddrs_ctx {struct ifaddrs_storage* last; struct ifaddrs_storage* first; struct ifaddrs_storage** hash; } ;
struct ifaddrmsg {size_t ifa_index; int /*<<< orphan*/  ifa_prefixlen; int /*<<< orphan*/  ifa_family; } ;

/* Variables and functions */
 size_t IFADDRS_HASH_SIZE ; 
#define  IFA_ADDRESS 135 
#define  IFA_BROADCAST 134 
#define  IFA_LABEL 133 
#define  IFA_LOCAL 132 
#define  IFLA_ADDRESS 131 
#define  IFLA_BROADCAST 130 
#define  IFLA_IFNAME 129 
#define  IFLA_STATS 128 
 void* NLMSG_DATA (struct nlmsghdr*) ; 
 struct rtattr* NLMSG_RTA (struct nlmsghdr*,int) ; 
 scalar_t__ NLMSG_RTAOK (struct rtattr*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  RTA_DATA (struct rtattr*) ; 
 int RTA_DATALEN (struct rtattr*) ; 
 struct rtattr* RTA_NEXT (struct rtattr*) ; 
 scalar_t__ RTM_NEWLINK ; 
 struct ifaddrs_storage* calloc (int,int) ; 
 int /*<<< orphan*/  copy_addr (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  copy_lladdr (int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ifaddrs_storage*) ; 
 int /*<<< orphan*/  gen_netmask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int netlink_msg_to_ifaddr(void *pctx, struct nlmsghdr *h)
{
	struct ifaddrs_ctx *ctx = pctx;
	struct ifaddrs_storage *ifs, *ifs0;
	struct ifinfomsg *ifi = NLMSG_DATA(h);
	struct ifaddrmsg *ifa = NLMSG_DATA(h);
	struct rtattr *rta;
	int stats_len = 0;

	if (h->nlmsg_type == RTM_NEWLINK) {
		for (rta = NLMSG_RTA(h, sizeof(*ifi)); NLMSG_RTAOK(rta, h); rta = RTA_NEXT(rta)) {
			if (rta->rta_type != IFLA_STATS) continue;
			stats_len = RTA_DATALEN(rta);
			break;
		}
	} else {
		for (ifs0 = ctx->hash[ifa->ifa_index % IFADDRS_HASH_SIZE]; ifs0; ifs0 = ifs0->hash_next)
			if (ifs0->index == ifa->ifa_index)
				break;
		if (!ifs0) return 0;
	}

	ifs = calloc(1, sizeof(struct ifaddrs_storage) + stats_len);
	if (ifs == 0) return -1;

	if (h->nlmsg_type == RTM_NEWLINK) {
		ifs->index = ifi->ifi_index;
		ifs->ifa.ifa_flags = ifi->ifi_flags;

		for (rta = NLMSG_RTA(h, sizeof(*ifi)); NLMSG_RTAOK(rta, h); rta = RTA_NEXT(rta)) {
			switch (rta->rta_type) {
			case IFLA_IFNAME:
				if (RTA_DATALEN(rta) < sizeof(ifs->name)) {
					memcpy(ifs->name, RTA_DATA(rta), RTA_DATALEN(rta));
					ifs->ifa.ifa_name = ifs->name;
				}
				break;
			case IFLA_ADDRESS:
				copy_lladdr(&ifs->ifa.ifa_addr, &ifs->addr, RTA_DATA(rta), RTA_DATALEN(rta), ifi->ifi_index, ifi->ifi_type);
				break;
			case IFLA_BROADCAST:
				copy_lladdr(&ifs->ifa.ifa_broadaddr, &ifs->ifu, RTA_DATA(rta), RTA_DATALEN(rta), ifi->ifi_index, ifi->ifi_type);
				break;
			case IFLA_STATS:
				ifs->ifa.ifa_data = (void*)(ifs+1);
				memcpy(ifs->ifa.ifa_data, RTA_DATA(rta), RTA_DATALEN(rta));
				break;
			}
		}
		if (ifs->ifa.ifa_name) {
			unsigned int bucket = ifs->index % IFADDRS_HASH_SIZE;
			ifs->hash_next = ctx->hash[bucket];
			ctx->hash[bucket] = ifs;
		}
	} else {
		ifs->ifa.ifa_name = ifs0->ifa.ifa_name;
		ifs->ifa.ifa_flags = ifs0->ifa.ifa_flags;
		for (rta = NLMSG_RTA(h, sizeof(*ifa)); NLMSG_RTAOK(rta, h); rta = RTA_NEXT(rta)) {
			switch (rta->rta_type) {
			case IFA_ADDRESS:
				/* If ifa_addr is already set we, received an IFA_LOCAL before
				 * so treat this as destination address */
				if (ifs->ifa.ifa_addr)
					copy_addr(&ifs->ifa.ifa_dstaddr, ifa->ifa_family, &ifs->ifu, RTA_DATA(rta), RTA_DATALEN(rta), ifa->ifa_index);
				else
					copy_addr(&ifs->ifa.ifa_addr, ifa->ifa_family, &ifs->addr, RTA_DATA(rta), RTA_DATALEN(rta), ifa->ifa_index);
				break;
			case IFA_BROADCAST:
				copy_addr(&ifs->ifa.ifa_broadaddr, ifa->ifa_family, &ifs->ifu, RTA_DATA(rta), RTA_DATALEN(rta), ifa->ifa_index);
				break;
			case IFA_LOCAL:
				/* If ifa_addr is set and we get IFA_LOCAL, assume we have
				 * a point-to-point network. Move address to correct field. */
				if (ifs->ifa.ifa_addr) {
					ifs->ifu = ifs->addr;
					ifs->ifa.ifa_dstaddr = &ifs->ifu.sa;
					memset(&ifs->addr, 0, sizeof(ifs->addr));
				}
				copy_addr(&ifs->ifa.ifa_addr, ifa->ifa_family, &ifs->addr, RTA_DATA(rta), RTA_DATALEN(rta), ifa->ifa_index);
				break;
			case IFA_LABEL:
				if (RTA_DATALEN(rta) < sizeof(ifs->name)) {
					memcpy(ifs->name, RTA_DATA(rta), RTA_DATALEN(rta));
					ifs->ifa.ifa_name = ifs->name;
				}
				break;
			}
		}
		if (ifs->ifa.ifa_addr)
			gen_netmask(&ifs->ifa.ifa_netmask, ifa->ifa_family, &ifs->netmask, ifa->ifa_prefixlen);
	}

	if (ifs->ifa.ifa_name) {
		if (!ctx->first) ctx->first = ifs;
		if (ctx->last) ctx->last->ifa.ifa_next = &ifs->ifa;
		ctx->last = ifs;
	} else {
		free(ifs);
	}
	return 0;
}