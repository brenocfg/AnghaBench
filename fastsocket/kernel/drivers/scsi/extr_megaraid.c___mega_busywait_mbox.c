#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  busy; } ;
struct TYPE_6__ {TYPE_1__ m_in; } ;
typedef  TYPE_2__ mbox_t ;
struct TYPE_7__ {TYPE_2__* mbox; } ;
typedef  TYPE_3__ adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
__mega_busywait_mbox (adapter_t *adapter)
{
	volatile mbox_t *mbox = adapter->mbox;
	long counter;

	for (counter = 0; counter < 10000; counter++) {
		if (!mbox->m_in.busy)
			return 0;
		udelay(100);
		cond_resched();
	}
	return -1;		/* give up after 1 second */
}