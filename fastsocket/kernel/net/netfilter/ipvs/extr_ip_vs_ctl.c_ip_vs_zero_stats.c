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
struct ip_vs_stats {int /*<<< orphan*/  lock; int /*<<< orphan*/  ustats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_vs_zero_estimator (struct ip_vs_stats*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ip_vs_zero_stats(struct ip_vs_stats *stats)
{
	spin_lock_bh(&stats->lock);

	memset(&stats->ustats, 0, sizeof(stats->ustats));
	ip_vs_zero_estimator(stats);

	spin_unlock_bh(&stats->lock);
}