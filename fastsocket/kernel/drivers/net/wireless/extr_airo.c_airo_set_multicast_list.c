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
struct net_device {int flags; scalar_t__ mc_count; struct airo_info* ml_priv; } ;
struct airo_info {int flags; int /*<<< orphan*/  thr_wait; int /*<<< orphan*/  jobs; int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_PROMISC ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  JOB_PROMISC ; 
 int /*<<< orphan*/  airo_set_promisc (struct airo_info*) ; 
 int /*<<< orphan*/  change_bit (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void airo_set_multicast_list(struct net_device *dev) {
	struct airo_info *ai = dev->ml_priv;

	if ((dev->flags ^ ai->flags) & IFF_PROMISC) {
		change_bit(FLAG_PROMISC, &ai->flags);
		if (down_trylock(&ai->sem) != 0) {
			set_bit(JOB_PROMISC, &ai->jobs);
			wake_up_interruptible(&ai->thr_wait);
		} else
			airo_set_promisc(ai);
	}

	if ((dev->flags&IFF_ALLMULTI)||dev->mc_count>0) {
		/* Turn on multicast.  (Should be already setup...) */
	}
}