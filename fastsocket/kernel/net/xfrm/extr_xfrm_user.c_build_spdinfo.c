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
typedef  int /*<<< orphan*/  u32 ;
struct xfrmu_spdinfo {int /*<<< orphan*/  spdhmcnt; int /*<<< orphan*/  spdhcnt; int /*<<< orphan*/  fwdscnt; int /*<<< orphan*/  outscnt; int /*<<< orphan*/  inscnt; int /*<<< orphan*/  fwdcnt; int /*<<< orphan*/  outcnt; int /*<<< orphan*/  incnt; } ;
struct xfrmu_spdhinfo {int /*<<< orphan*/  spdhmcnt; int /*<<< orphan*/  spdhcnt; int /*<<< orphan*/  fwdscnt; int /*<<< orphan*/  outscnt; int /*<<< orphan*/  inscnt; int /*<<< orphan*/  fwdcnt; int /*<<< orphan*/  outcnt; int /*<<< orphan*/  incnt; } ;
struct xfrmk_spdinfo {int /*<<< orphan*/  spdhmcnt; int /*<<< orphan*/  spdhcnt; int /*<<< orphan*/  fwdscnt; int /*<<< orphan*/  outscnt; int /*<<< orphan*/  inscnt; int /*<<< orphan*/  fwdcnt; int /*<<< orphan*/  outcnt; int /*<<< orphan*/  incnt; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
typedef  int /*<<< orphan*/  sph ;
typedef  int /*<<< orphan*/  spc ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct xfrmu_spdinfo*) ; 
 int /*<<< orphan*/  XFRMA_SPD_HINFO ; 
 int /*<<< orphan*/  XFRMA_SPD_INFO ; 
 int /*<<< orphan*/  XFRM_MSG_NEWSPDINFO ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/ * nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_spd_getinfo (struct xfrmk_spdinfo*) ; 

__attribute__((used)) static int build_spdinfo(struct sk_buff *skb, u32 pid, u32 seq, u32 flags)
{
	struct xfrmk_spdinfo si;
	struct xfrmu_spdinfo spc;
	struct xfrmu_spdhinfo sph;
	struct nlmsghdr *nlh;
	u32 *f;

	nlh = nlmsg_put(skb, pid, seq, XFRM_MSG_NEWSPDINFO, sizeof(u32), 0);
	if (nlh == NULL) /* shouldnt really happen ... */
		return -EMSGSIZE;

	f = nlmsg_data(nlh);
	*f = flags;
	xfrm_spd_getinfo(&si);
	spc.incnt = si.incnt;
	spc.outcnt = si.outcnt;
	spc.fwdcnt = si.fwdcnt;
	spc.inscnt = si.inscnt;
	spc.outscnt = si.outscnt;
	spc.fwdscnt = si.fwdscnt;
	sph.spdhcnt = si.spdhcnt;
	sph.spdhmcnt = si.spdhmcnt;

	NLA_PUT(skb, XFRMA_SPD_INFO, sizeof(spc), &spc);
	NLA_PUT(skb, XFRMA_SPD_HINFO, sizeof(sph), &sph);

	return nlmsg_end(skb, nlh);

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}