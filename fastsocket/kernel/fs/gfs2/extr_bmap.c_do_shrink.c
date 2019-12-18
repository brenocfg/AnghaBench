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
struct inode {int dummy; } ;
struct gfs2_inode {int dummy; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 scalar_t__ gfs2_is_stuffed (struct gfs2_inode*) ; 
 int trunc_dealloc (struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 int trunc_end (struct gfs2_inode*) ; 
 int trunc_start (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_shrink(struct inode *inode, u64 oldsize, u64 newsize)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	int error;

	error = trunc_start(inode, oldsize, newsize);
	if (error < 0)
		return error;
	if (gfs2_is_stuffed(ip))
		return 0;

	error = trunc_dealloc(ip, newsize);
	if (error == 0)
		error = trunc_end(ip);

	return error;
}