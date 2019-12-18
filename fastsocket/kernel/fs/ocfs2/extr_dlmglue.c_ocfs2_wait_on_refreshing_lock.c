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
struct ocfs2_lock_res {int /*<<< orphan*/  l_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_LOCK_REFRESHING ; 
 int /*<<< orphan*/  ocfs2_check_wait_flag (struct ocfs2_lock_res*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ocfs2_wait_on_refreshing_lock(struct ocfs2_lock_res *lockres)

{
	wait_event(lockres->l_event,
		   !ocfs2_check_wait_flag(lockres, OCFS2_LOCK_REFRESHING));
}