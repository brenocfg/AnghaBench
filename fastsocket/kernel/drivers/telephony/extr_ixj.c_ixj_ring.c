#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ringing; } ;
struct TYPE_8__ {char maxrings; TYPE_1__ flags; } ;
typedef  TYPE_2__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int hertz ; 
 int ixj_hookstate (TYPE_2__*) ; 
 int /*<<< orphan*/  ixj_ring_off (TYPE_2__*) ; 
 int /*<<< orphan*/  ixj_ring_on (TYPE_2__*) ; 
 int jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static int ixj_ring(IXJ *j)
{
	char cntr;
	unsigned long jif;

	j->flags.ringing = 1;
	if (ixj_hookstate(j) & 1) {
		ixj_ring_off(j);
		j->flags.ringing = 0;
		return 1;
	}
	for (cntr = 0; cntr < j->maxrings; cntr++) {
		jif = jiffies + (1 * hertz);
		ixj_ring_on(j);
		while (time_before(jiffies, jif)) {
			if (ixj_hookstate(j) & 1) {
				ixj_ring_off(j);
				j->flags.ringing = 0;
				return 1;
			}
			schedule_timeout_interruptible(1);
			if (signal_pending(current))
				break;
		}
		jif = jiffies + (3 * hertz);
		ixj_ring_off(j);
		while (time_before(jiffies, jif)) {
			if (ixj_hookstate(j) & 1) {
				msleep(10);
				if (ixj_hookstate(j) & 1) {
					j->flags.ringing = 0;
					return 1;
				}
			}
			schedule_timeout_interruptible(1);
			if (signal_pending(current))
				break;
		}
	}
	ixj_ring_off(j);
	j->flags.ringing = 0;
	return 0;
}