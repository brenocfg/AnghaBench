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
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int /*<<< orphan*/  C_VATTR ; 
 int /*<<< orphan*/  coda_flag_inode (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void coda_dir_update_mtime(struct inode *dir)
{
#ifdef REQUERY_VENUS_FOR_MTIME
	/* invalidate the directory cnode's attributes so we refetch the
	 * attributes from venus next time the inode is referenced */
	coda_flag_inode(dir, C_VATTR);
#else
	/* optimistically we can also act as if our nose bleeds. The
	 * granularity of the mtime is coarse anyways so we might actually be
	 * right most of the time. Note: we only do this for directories. */
	dir->i_mtime = dir->i_ctime = CURRENT_TIME_SEC;
#endif
}