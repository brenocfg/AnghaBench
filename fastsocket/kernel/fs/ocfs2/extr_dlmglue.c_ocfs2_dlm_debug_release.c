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
struct seq_file {struct ocfs2_dlm_seq_priv* private; } ;
struct ocfs2_lock_res {int dummy; } ;
struct ocfs2_dlm_seq_priv {int /*<<< orphan*/  p_dlm_debug; struct ocfs2_lock_res p_iter_res; } ;
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_put_dlm_debug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_remove_lockres_tracking (struct ocfs2_lock_res*) ; 
 int seq_release_private (struct inode*,struct file*) ; 

__attribute__((used)) static int ocfs2_dlm_debug_release(struct inode *inode, struct file *file)
{
	struct seq_file *seq = (struct seq_file *) file->private_data;
	struct ocfs2_dlm_seq_priv *priv = seq->private;
	struct ocfs2_lock_res *res = &priv->p_iter_res;

	ocfs2_remove_lockres_tracking(res);
	ocfs2_put_dlm_debug(priv->p_dlm_debug);
	return seq_release_private(inode, file);
}