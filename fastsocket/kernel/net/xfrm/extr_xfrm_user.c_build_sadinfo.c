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
struct xfrmu_sadhinfo {int /*<<< orphan*/  sadhcnt; int /*<<< orphan*/  sadhmcnt; } ;
struct xfrmk_sadinfo {int /*<<< orphan*/  sadcnt; int /*<<< orphan*/  sadhcnt; int /*<<< orphan*/  sadhmcnt; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
typedef  int /*<<< orphan*/  sh ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct xfrmu_sadhinfo*) ; 
 int /*<<< orphan*/  NLA_PUT_U32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFRMA_SAD_CNT ; 
 int /*<<< orphan*/  XFRMA_SAD_HINFO ; 
 int /*<<< orphan*/  XFRM_MSG_NEWSADINFO ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/ * nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_sad_getinfo (struct xfrmk_sadinfo*) ; 

__attribute__((used)) static int build_sadinfo(struct sk_buff *skb, u32 pid, u32 seq, u32 flags)
{
	struct xfrmk_sadinfo si;
	struct xfrmu_sadhinfo sh;
	struct nlmsghdr *nlh;
	u32 *f;

	nlh = nlmsg_put(skb, pid, seq, XFRM_MSG_NEWSADINFO, sizeof(u32), 0);
	if (nlh == NULL) /* shouldnt really happen ... */
		return -EMSGSIZE;

	f = nlmsg_data(nlh);
	*f = flags;
	xfrm_sad_getinfo(&si);

	sh.sadhmcnt = si.sadhmcnt;
	sh.sadhcnt = si.sadhcnt;

	NLA_PUT_U32(skb, XFRMA_SAD_CNT, si.sadcnt);
	NLA_PUT(skb, XFRMA_SAD_HINFO, sizeof(sh), &sh);

	return nlmsg_end(skb, nlh);

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}