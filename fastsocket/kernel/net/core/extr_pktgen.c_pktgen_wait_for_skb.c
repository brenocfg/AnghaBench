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
struct pktgen_dev {int /*<<< orphan*/  idle_acc; TYPE_1__* skb; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  ktime_now () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  pktgen_resched (struct pktgen_dev*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pktgen_wait_for_skb(struct pktgen_dev *pkt_dev)
{
	ktime_t idle_start = ktime_now();

	while (atomic_read(&(pkt_dev->skb->users)) != 1) {
		if (signal_pending(current))
			break;

		if (need_resched())
			pktgen_resched(pkt_dev);
		else
			cpu_relax();
	}
	pkt_dev->idle_acc += ktime_to_ns(ktime_sub(ktime_now(), idle_start));
}