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
struct i2400m {int boot_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  __i2400m_dev_reset_handle ; 
 int i2400m_schedule_work (struct i2400m*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

int i2400m_dev_reset_handle(struct i2400m *i2400m)
{
	i2400m->boot_mode = 1;
	wmb();		/* Make sure i2400m_msg_to_dev() sees boot_mode */
	return i2400m_schedule_work(i2400m, __i2400m_dev_reset_handle,
				    GFP_ATOMIC);
}