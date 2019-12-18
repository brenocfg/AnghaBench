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
struct gfs2_glock {scalar_t__ gl_state; int /*<<< orphan*/  gl_work; int /*<<< orphan*/  gl_spin; } ;

/* Variables and functions */
 scalar_t__ LM_ST_UNLOCKED ; 
 int /*<<< orphan*/ * find_first_holder (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_glock_put (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_glock_remove_from_lru (struct gfs2_glock*) ; 
 int /*<<< orphan*/  glock_workqueue ; 
 int /*<<< orphan*/  handle_callback (struct gfs2_glock*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_glock(struct gfs2_glock *gl)
{
	gfs2_glock_remove_from_lru(gl);

	spin_lock(&gl->gl_spin);
	if (find_first_holder(gl) == NULL && gl->gl_state != LM_ST_UNLOCKED)
		handle_callback(gl, LM_ST_UNLOCKED, 0, false);
	spin_unlock(&gl->gl_spin);
	if (queue_delayed_work(glock_workqueue, &gl->gl_work, 0) == 0)
		gfs2_glock_put(gl);
}