#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_dir_lookup_result {TYPE_1__* dl_entry; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {scalar_t__ ip_blkno; } ;
struct TYPE_3__ {int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_2__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,char const*,int /*<<< orphan*/ *,unsigned long long) ; 
 int ocfs2_find_entry (char const*,int,struct inode*,struct ocfs2_dir_lookup_result*) ; 

int ocfs2_find_files_on_disk(const char *name,
			     int namelen,
			     u64 *blkno,
			     struct inode *inode,
			     struct ocfs2_dir_lookup_result *lookup)
{
	int status = -ENOENT;

	mlog(0, "name=%.*s, blkno=%p, inode=%llu\n", namelen, name, blkno,
	     (unsigned long long)OCFS2_I(inode)->ip_blkno);

	status = ocfs2_find_entry(name, namelen, inode, lookup);
	if (status)
		goto leave;

	*blkno = le64_to_cpu(lookup->dl_entry->inode);

	status = 0;
leave:

	return status;
}