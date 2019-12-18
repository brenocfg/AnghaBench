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
struct gfs2_glock {int /*<<< orphan*/  gl_flags; int /*<<< orphan*/  gl_lru; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLF_LRU ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lru_count ; 
 int /*<<< orphan*/  lru_list ; 
 int /*<<< orphan*/  lru_lock ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void gfs2_glock_add_to_lru(struct gfs2_glock *gl)
{
	spin_lock(&lru_lock);

	if (!list_empty(&gl->gl_lru))
		list_del_init(&gl->gl_lru);
	else
		atomic_inc(&lru_count);

	list_add_tail(&gl->gl_lru, &lru_list);
	set_bit(GLF_LRU, &gl->gl_flags);
	spin_unlock(&lru_lock);
}