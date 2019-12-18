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
struct rds_message {int /*<<< orphan*/  m_flags; int /*<<< orphan*/  m_flush_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_MSG_MAPPED ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

void rds_message_wait(struct rds_message *rm)
{
	wait_event_interruptible(rm->m_flush_wait,
			!test_bit(RDS_MSG_MAPPED, &rm->m_flags));
}