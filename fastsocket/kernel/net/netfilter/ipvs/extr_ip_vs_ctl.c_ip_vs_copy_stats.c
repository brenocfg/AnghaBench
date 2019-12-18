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
struct ip_vs_stats_user {int dummy; } ;
struct ip_vs_stats {int /*<<< orphan*/  lock; int /*<<< orphan*/  ustats; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct ip_vs_stats_user*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ip_vs_copy_stats(struct ip_vs_stats_user *dst, struct ip_vs_stats *src)
{
	spin_lock_bh(&src->lock);
	memcpy(dst, &src->ustats, sizeof(*dst));
	spin_unlock_bh(&src->lock);
}