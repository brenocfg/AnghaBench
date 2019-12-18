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
struct rds_ib_connection {int /*<<< orphan*/  i_signaled_sends; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_sub_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_ib_ring_empty_wait ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rds_ib_sub_signaled(struct rds_ib_connection *ic, int nr)
{
	if ((atomic_sub_return(nr, &ic->i_signaled_sends) == 0) &&
	    waitqueue_active(&rds_ib_ring_empty_wait))
		wake_up(&rds_ib_ring_empty_wait);
	BUG_ON(atomic_read(&ic->i_signaled_sends) < 0);
}