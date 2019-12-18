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
struct ocfs2_dir_lookup_result {int /*<<< orphan*/ * member_0; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int EEXIST ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  mlog_entry (char*,unsigned long long,int,char const*) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 scalar_t__ ocfs2_find_entry (char const*,int,struct inode*,struct ocfs2_dir_lookup_result*) ; 
 int /*<<< orphan*/  ocfs2_free_dir_lookup_result (struct ocfs2_dir_lookup_result*) ; 

int ocfs2_check_dir_for_entry(struct inode *dir,
			      const char *name,
			      int namelen)
{
	int ret;
	struct ocfs2_dir_lookup_result lookup = { NULL, };

	mlog_entry("dir %llu, name '%.*s'\n",
		   (unsigned long long)OCFS2_I(dir)->ip_blkno, namelen, name);

	ret = -EEXIST;
	if (ocfs2_find_entry(name, namelen, dir, &lookup) == 0)
		goto bail;

	ret = 0;
bail:
	ocfs2_free_dir_lookup_result(&lookup);

	mlog_exit(ret);
	return ret;
}