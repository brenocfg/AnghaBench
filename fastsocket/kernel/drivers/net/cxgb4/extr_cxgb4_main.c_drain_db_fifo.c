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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SGE_DBFIFO_STATUS ; 
 scalar_t__ G_HP_COUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ G_LP_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int) ; 

__attribute__((used)) static void drain_db_fifo(struct adapter *adap, int usecs)
{
	u32 v;

	do {
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_timeout(usecs_to_jiffies(usecs));
		v = t4_read_reg(adap, A_SGE_DBFIFO_STATUS);
		if (G_LP_COUNT(v) == 0 && G_HP_COUNT(v) == 0)
			break;
	} while (1);
}