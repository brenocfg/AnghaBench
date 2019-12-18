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

/* Variables and functions */
 int /*<<< orphan*/  LCK_ATTR_NULL ; 
 int /*<<< orphan*/  LCK_GRP_ATTR_NULL ; 
 int /*<<< orphan*/  lck_grp_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_spin_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oslog_stream_lock ; 
 int /*<<< orphan*/  oslog_stream_lock_grp ; 

void
oslog_lock_init(void)
{
	lck_grp_init(&oslog_stream_lock_grp, "oslog stream", LCK_GRP_ATTR_NULL);
	lck_spin_init(&oslog_stream_lock, &oslog_stream_lock_grp, LCK_ATTR_NULL);
}