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
typedef  scalar_t__ u32 ;
struct veno {scalar_t__ basertt; int /*<<< orphan*/  cntrtt; int /*<<< orphan*/  minrtt; } ;
struct sock {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 struct veno* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tcp_veno_pkts_acked(struct sock *sk, u32 cnt, s32 rtt_us)
{
	struct veno *veno = inet_csk_ca(sk);
	u32 vrtt;

	if (rtt_us < 0)
		return;

	/* Never allow zero rtt or baseRTT */
	vrtt = rtt_us + 1;

	/* Filter to find propagation delay: */
	if (vrtt < veno->basertt)
		veno->basertt = vrtt;

	/* Find the min rtt during the last rtt to find
	 * the current prop. delay + queuing delay:
	 */
	veno->minrtt = min(veno->minrtt, vrtt);
	veno->cntrtt++;
}