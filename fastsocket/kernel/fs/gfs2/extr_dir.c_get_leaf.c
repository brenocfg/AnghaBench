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
typedef  int /*<<< orphan*/  u64 ;
struct gfs2_inode {int /*<<< orphan*/  i_inode; int /*<<< orphan*/  i_gl; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIO_WAIT ; 
 int EIO ; 
 int /*<<< orphan*/  GFS2_METATYPE_LF ; 
 int /*<<< orphan*/  GFS2_SB (int /*<<< orphan*/ *) ; 
 int gfs2_meta_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 scalar_t__ gfs2_metatype_check (int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_leaf(struct gfs2_inode *dip, u64 leaf_no,
		    struct buffer_head **bhp)
{
	int error;

	error = gfs2_meta_read(dip->i_gl, leaf_no, DIO_WAIT, bhp);
	if (!error && gfs2_metatype_check(GFS2_SB(&dip->i_inode), *bhp, GFS2_METATYPE_LF)) {
		/* printk(KERN_INFO "block num=%llu\n", leaf_no); */
		error = -EIO;
	}

	return error;
}