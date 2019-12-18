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
struct ocfs2_file_private {int /*<<< orphan*/  fp_flock; int /*<<< orphan*/  fp_mutex; struct file* fp_file; } ;
struct inode {int dummy; } ;
struct file {struct ocfs2_file_private* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ocfs2_file_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_file_lock_res_init (int /*<<< orphan*/ *,struct ocfs2_file_private*) ; 

__attribute__((used)) static int ocfs2_init_file_private(struct inode *inode, struct file *file)
{
	struct ocfs2_file_private *fp;

	fp = kzalloc(sizeof(struct ocfs2_file_private), GFP_KERNEL);
	if (!fp)
		return -ENOMEM;

	fp->fp_file = file;
	mutex_init(&fp->fp_mutex);
	ocfs2_file_lock_res_init(&fp->fp_flock, fp);
	file->private_data = fp;

	return 0;
}