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
struct rds_sock {int /*<<< orphan*/  rs_lock; int /*<<< orphan*/  rs_cong_mask; scalar_t__ rs_cong_monitor; } ;
struct rds_cong_map {int /*<<< orphan*/  m_waitq; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  RDS_CONG_MONITOR_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_cong_test_bit (struct rds_cong_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_cong_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_cong_send_blocked ; 
 int /*<<< orphan*/  s_cong_send_error ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int rds_cong_wait(struct rds_cong_map *map, __be16 port, int nonblock,
		  struct rds_sock *rs)
{
	if (!rds_cong_test_bit(map, port))
		return 0;
	if (nonblock) {
		if (rs && rs->rs_cong_monitor) {
			unsigned long flags;

			/* It would have been nice to have an atomic set_bit on
			 * a uint64_t. */
			spin_lock_irqsave(&rs->rs_lock, flags);
			rs->rs_cong_mask |= RDS_CONG_MONITOR_MASK(ntohs(port));
			spin_unlock_irqrestore(&rs->rs_lock, flags);

			/* Test again - a congestion update may have arrived in
			 * the meantime. */
			if (!rds_cong_test_bit(map, port))
				return 0;
		}
		rds_stats_inc(s_cong_send_error);
		return -ENOBUFS;
	}

	rds_stats_inc(s_cong_send_blocked);
	rdsdebug("waiting on map %p for port %u\n", map, be16_to_cpu(port));

	return wait_event_interruptible(map->m_waitq,
					!rds_cong_test_bit(map, port));
}