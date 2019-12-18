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
struct gfs2_glock {int /*<<< orphan*/  gl_revokes; int /*<<< orphan*/  gl_ail_count; int /*<<< orphan*/  gl_ail_list; int /*<<< orphan*/  gl_lru; int /*<<< orphan*/  gl_holders; int /*<<< orphan*/  gl_spin; int /*<<< orphan*/  gl_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_BL_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gfs2_init_glock_once(void *foo)
{
	struct gfs2_glock *gl = foo;

	INIT_HLIST_BL_NODE(&gl->gl_list);
	spin_lock_init(&gl->gl_spin);
	INIT_LIST_HEAD(&gl->gl_holders);
	INIT_LIST_HEAD(&gl->gl_lru);
	INIT_LIST_HEAD(&gl->gl_ail_list);
	atomic_set(&gl->gl_ail_count, 0);
	atomic_set(&gl->gl_revokes, 0);
}