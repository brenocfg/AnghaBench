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
struct rtattr {int rta_type; } ;
struct nlmsghdr {scalar_t__ nlmsg_type; } ;
struct ifnamemap {int index; int namelen; unsigned int hash_next; int /*<<< orphan*/  name; } ;
struct ifnameindexctx {unsigned int* hash; size_t num; size_t allocated; int str_bytes; struct ifnamemap* list; } ;
struct ifinfomsg {int ifi_index; } ;
struct ifaddrmsg {int ifa_index; } ;

/* Variables and functions */
 int IFADDRS_HASH_SIZE ; 
 int IFA_LABEL ; 
 int IFLA_IFNAME ; 
 int IFNAMSIZ ; 
 void* NLMSG_DATA (struct nlmsghdr*) ; 
 struct rtattr* NLMSG_RTA (struct nlmsghdr*,int) ; 
 scalar_t__ NLMSG_RTAOK (struct rtattr*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  RTA_DATA (struct rtattr*) ; 
 int RTA_DATALEN (struct rtattr*) ; 
 struct rtattr* RTA_NEXT (struct rtattr*) ; 
 scalar_t__ RTM_NEWLINK ; 
 int SIZE_MAX ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ifnamemap* realloc (struct ifnamemap*,size_t) ; 

__attribute__((used)) static int netlink_msg_to_nameindex(void *pctx, struct nlmsghdr *h)
{
	struct ifnameindexctx *ctx = pctx;
	struct ifnamemap *map;
	struct rtattr *rta;
	unsigned int i;
	int index, type, namelen, bucket;

	if (h->nlmsg_type == RTM_NEWLINK) {
		struct ifinfomsg *ifi = NLMSG_DATA(h);
		index = ifi->ifi_index;
		type = IFLA_IFNAME;
		rta = NLMSG_RTA(h, sizeof(*ifi));
	} else {
		struct ifaddrmsg *ifa = NLMSG_DATA(h);
		index = ifa->ifa_index;
		type = IFA_LABEL;
		rta = NLMSG_RTA(h, sizeof(*ifa));
	}
	for (; NLMSG_RTAOK(rta, h); rta = RTA_NEXT(rta)) {
		if (rta->rta_type != type) continue;

		namelen = RTA_DATALEN(rta) - 1;
		if (namelen > IFNAMSIZ) return 0;

		/* suppress duplicates */
		bucket = index % IFADDRS_HASH_SIZE;
		i = ctx->hash[bucket];
		while (i) {
			map = &ctx->list[i-1];
			if (map->index == index &&
			    map->namelen == namelen &&
			    memcmp(map->name, RTA_DATA(rta), namelen) == 0)
				return 0;
			i = map->hash_next;
		}

		if (ctx->num >= ctx->allocated) {
			size_t a = ctx->allocated ? ctx->allocated * 2 + 1 : 8;
			if (a > SIZE_MAX/sizeof *map) return -1;
			map = realloc(ctx->list, a * sizeof *map);
			if (!map) return -1;
			ctx->list = map;
			ctx->allocated = a;
		}
		map = &ctx->list[ctx->num];
		map->index = index;
		map->namelen = namelen;
		memcpy(map->name, RTA_DATA(rta), namelen);
		ctx->str_bytes += namelen + 1;
		ctx->num++;
		map->hash_next = ctx->hash[bucket];
		ctx->hash[bucket] = ctx->num;
		return 0;
	}
	return 0;
}