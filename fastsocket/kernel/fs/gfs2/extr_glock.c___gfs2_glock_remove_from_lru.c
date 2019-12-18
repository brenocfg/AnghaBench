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
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lru_count ; 

__attribute__((used)) static void __gfs2_glock_remove_from_lru(struct gfs2_glock *gl)
{
	if (!list_empty(&gl->gl_lru)) {
		list_del_init(&gl->gl_lru);
		atomic_dec(&lru_count);
		clear_bit(GLF_LRU, &gl->gl_flags);
	}
}