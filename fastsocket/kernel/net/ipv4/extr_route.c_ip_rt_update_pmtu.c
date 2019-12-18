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
typedef  int u32 ;
struct dst_entry {int* metrics; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETEVENT_PMTU_UPDATE ; 
 int RTAX_LOCK ; 
 int RTAX_MTU ; 
 int /*<<< orphan*/  call_netevent_notifiers (int /*<<< orphan*/ ,struct dst_entry*) ; 
 int /*<<< orphan*/  dst_metric_locked (struct dst_entry*,int) ; 
 int dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_set_expires (struct dst_entry*,int /*<<< orphan*/ ) ; 
 int ip_rt_min_pmtu ; 
 int /*<<< orphan*/  ip_rt_mtu_expires ; 

__attribute__((used)) static void ip_rt_update_pmtu(struct dst_entry *dst, u32 mtu)
{
	if (dst_mtu(dst) > mtu && mtu >= 68 &&
	    !(dst_metric_locked(dst, RTAX_MTU))) {
		if (mtu < ip_rt_min_pmtu) {
			mtu = ip_rt_min_pmtu;
			dst->metrics[RTAX_LOCK-1] |= (1 << RTAX_MTU);
		}
		dst->metrics[RTAX_MTU-1] = mtu;
		dst_set_expires(dst, ip_rt_mtu_expires);
		call_netevent_notifiers(NETEVENT_PMTU_UPDATE, dst);
	}
}