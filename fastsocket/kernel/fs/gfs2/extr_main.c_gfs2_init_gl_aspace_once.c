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
struct gfs2_glock {int dummy; } ;
struct address_space {int /*<<< orphan*/  i_mmap_nonlinear; int /*<<< orphan*/  i_mmap; int /*<<< orphan*/  private_lock; int /*<<< orphan*/  private_list; int /*<<< orphan*/  i_mmap_lock; int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  page_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_RAW_PRIO_TREE_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_init_glock_once (struct gfs2_glock*) ; 
 int /*<<< orphan*/  memset (struct address_space*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gfs2_init_gl_aspace_once(void *foo)
{
	struct gfs2_glock *gl = foo;
	struct address_space *mapping = (struct address_space *)(gl + 1);

	gfs2_init_glock_once(gl);
	memset(mapping, 0, sizeof(*mapping));
	INIT_RADIX_TREE(&mapping->page_tree, GFP_ATOMIC);
	spin_lock_init(&mapping->tree_lock);
	spin_lock_init(&mapping->i_mmap_lock);
	INIT_LIST_HEAD(&mapping->private_list);
	spin_lock_init(&mapping->private_lock);
	INIT_RAW_PRIO_TREE_ROOT(&mapping->i_mmap);
	INIT_LIST_HEAD(&mapping->i_mmap_nonlinear);
}