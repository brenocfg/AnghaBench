#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct file* file; } ;
struct splice_desc {size_t total_len; unsigned int flags; int pos; int num_spliced; TYPE_1__ u; } ;
struct pipe_inode_info {TYPE_5__* inode; } ;
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_9__ {TYPE_3__* dentry; } ;
struct file {TYPE_4__ f_path; struct address_space* f_mapping; } ;
struct address_space {struct inode* host; } ;
typedef  int ssize_t ;
typedef  int loff_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct TYPE_8__ {TYPE_2__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_MUTEX_CHILD ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  balance_dirty_pages_ratelimited_nr (struct address_space*,unsigned long) ; 
 int generic_write_sync (struct file*,int,int) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct file*,struct pipe_inode_info*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ocfs2_rw_lock (struct inode*,int) ; 
 int /*<<< orphan*/  ocfs2_rw_unlock (struct inode*,int) ; 
 int ocfs2_splice_to_file (struct pipe_inode_info*,struct file*,struct splice_desc*) ; 
 int /*<<< orphan*/  splice_from_pipe_begin (struct splice_desc*) ; 
 int /*<<< orphan*/  splice_from_pipe_end (struct pipe_inode_info*,struct splice_desc*) ; 
 int splice_from_pipe_next (struct pipe_inode_info*,struct splice_desc*) ; 

__attribute__((used)) static ssize_t ocfs2_file_splice_write(struct pipe_inode_info *pipe,
				       struct file *out,
				       loff_t *ppos,
				       size_t len,
				       unsigned int flags)
{
	int ret;
	struct address_space *mapping = out->f_mapping;
	struct inode *inode = mapping->host;
	struct splice_desc sd = {
		.total_len = len,
		.flags = flags,
		.pos = *ppos,
		.u.file = out,
	};

	mlog_entry("(0x%p, 0x%p, %u, '%.*s')\n", out, pipe,
		   (unsigned int)len,
		   out->f_path.dentry->d_name.len,
		   out->f_path.dentry->d_name.name);

	if (pipe->inode)
		mutex_lock_nested(&pipe->inode->i_mutex, I_MUTEX_PARENT);

	splice_from_pipe_begin(&sd);
	do {
		ret = splice_from_pipe_next(pipe, &sd);
		if (ret <= 0)
			break;

		mutex_lock_nested(&inode->i_mutex, I_MUTEX_CHILD);
		ret = ocfs2_rw_lock(inode, 1);
		if (ret < 0)
			mlog_errno(ret);
		else {
			ret = ocfs2_splice_to_file(pipe, out, &sd);
			ocfs2_rw_unlock(inode, 1);
		}
		mutex_unlock(&inode->i_mutex);
	} while (ret > 0);
	splice_from_pipe_end(pipe, &sd);

	if (pipe->inode)
		mutex_unlock(&pipe->inode->i_mutex);

	if (sd.num_spliced)
		ret = sd.num_spliced;

	if (ret > 0) {
		unsigned long nr_pages;
		int err;

		nr_pages = (ret + PAGE_CACHE_SIZE - 1) >> PAGE_CACHE_SHIFT;

		err = generic_write_sync(out, *ppos, ret);
		if (err)
			ret = err;
		else
			*ppos += ret;

		balance_dirty_pages_ratelimited_nr(mapping, nr_pages);
	}

	mlog_exit(ret);
	return ret;
}