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
struct adapter {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_ALERT (char*,int /*<<< orphan*/ ) ; 
 int FULL_INIT_DONE ; 
 int /*<<< orphan*/  t1_interrupts_disable (struct adapter*) ; 
 int /*<<< orphan*/  t1_sge_stop (int /*<<< orphan*/ ) ; 

void t1_fatal_err(struct adapter *adapter)
{
	if (adapter->flags & FULL_INIT_DONE) {
		t1_sge_stop(adapter->sge);
		t1_interrupts_disable(adapter);
	}
	CH_ALERT("%s: encountered fatal error, operation suspended\n",
		 adapter->name);
}