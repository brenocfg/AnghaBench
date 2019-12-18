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
struct svc_cacherep {int /*<<< orphan*/  c_lru; int /*<<< orphan*/  c_timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  RC_EXPIRE ; 
 int /*<<< orphan*/  cache_cleaner ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lru_head ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lru_put_end(struct svc_cacherep *rp)
{
	rp->c_timestamp = jiffies;
	list_move_tail(&rp->c_lru, &lru_head);
	schedule_delayed_work(&cache_cleaner, RC_EXPIRE);
}