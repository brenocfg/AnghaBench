#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct address_space* i_mapping; int /*<<< orphan*/  i_mode; } ;
struct gfs2_inode {TYPE_1__ i_inode; int /*<<< orphan*/  i_flags; } ;
struct gfs2_glock {scalar_t__ gl_state; int /*<<< orphan*/  gl_flags; int /*<<< orphan*/  gl_sbd; struct gfs2_inode* gl_object; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GIF_SW_PAGED ; 
 int /*<<< orphan*/  GLF_DIRTY ; 
 scalar_t__ LM_ST_EXCLUSIVE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int filemap_fdatawait (struct address_space*) ; 
 int /*<<< orphan*/  filemap_fdatawrite (struct address_space*) ; 
 int /*<<< orphan*/  gfs2_ail_empty_gl (struct gfs2_glock*) ; 
 struct address_space* gfs2_glock2aspace (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_log_flush (int /*<<< orphan*/ ,struct gfs2_glock*) ; 
 int /*<<< orphan*/  mapping_set_error (struct address_space*,int) ; 
 int /*<<< orphan*/  smp_mb__before_clear_bit () ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unmap_shared_mapping_range (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inode_go_sync(struct gfs2_glock *gl)
{
	struct gfs2_inode *ip = gl->gl_object;
	struct address_space *metamapping = gfs2_glock2aspace(gl);
	int error;

	if (ip && !S_ISREG(ip->i_inode.i_mode))
		ip = NULL;
	if (ip && test_and_clear_bit(GIF_SW_PAGED, &ip->i_flags))
		unmap_shared_mapping_range(ip->i_inode.i_mapping, 0, 0);
	if (!test_and_clear_bit(GLF_DIRTY, &gl->gl_flags))
		return;

	BUG_ON(gl->gl_state != LM_ST_EXCLUSIVE);

	gfs2_log_flush(gl->gl_sbd, gl);
	filemap_fdatawrite(metamapping);
	if (ip) {
		struct address_space *mapping = ip->i_inode.i_mapping;
		filemap_fdatawrite(mapping);
		error = filemap_fdatawait(mapping);
		mapping_set_error(mapping, error);
	}
	error = filemap_fdatawait(metamapping);
	mapping_set_error(metamapping, error);
	gfs2_ail_empty_gl(gl);
	/*
	 * Writeback of the data mapping may cause the dirty flag to be set
	 * so we have to clear it again here.
	 */
	smp_mb__before_clear_bit();
	clear_bit(GLF_DIRTY, &gl->gl_flags);
}