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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int plen; } ;
struct rt6_info {int /*<<< orphan*/  rt6i_flags; TYPE_1__ rt6i_dst; } ;
struct dst_entry {int /*<<< orphan*/ * metrics; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPV6_MIN_MTU ; 
 int /*<<< orphan*/  NETEVENT_PMTU_UPDATE ; 
 int RTAX_FEATURES ; 
 int /*<<< orphan*/  RTAX_FEATURE_ALLFRAG ; 
 int RTAX_MTU ; 
 int /*<<< orphan*/  RTF_MODIFIED ; 
 int /*<<< orphan*/  call_netevent_notifiers (int /*<<< orphan*/ ,struct dst_entry*) ; 
 int /*<<< orphan*/  dst_mtu (struct dst_entry*) ; 

__attribute__((used)) static void ip6_rt_update_pmtu(struct dst_entry *dst, u32 mtu)
{
	struct rt6_info *rt6 = (struct rt6_info*)dst;

	if (mtu < dst_mtu(dst) && rt6->rt6i_dst.plen == 128) {
		rt6->rt6i_flags |= RTF_MODIFIED;
		if (mtu < IPV6_MIN_MTU) {
			mtu = IPV6_MIN_MTU;
			dst->metrics[RTAX_FEATURES-1] |= RTAX_FEATURE_ALLFRAG;
		}
		dst->metrics[RTAX_MTU-1] = mtu;
		call_netevent_notifiers(NETEVENT_PMTU_UPDATE, dst);
	}
}