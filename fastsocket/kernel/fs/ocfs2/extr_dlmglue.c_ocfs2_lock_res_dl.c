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
struct ocfs2_lock_res {scalar_t__ l_type; scalar_t__ l_priv; } ;
struct ocfs2_dentry_lock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ OCFS2_LOCK_TYPE_DENTRY ; 

__attribute__((used)) static inline struct ocfs2_dentry_lock *ocfs2_lock_res_dl(struct ocfs2_lock_res *lockres)
{
	BUG_ON(lockres->l_type != OCFS2_LOCK_TYPE_DENTRY);

	return (struct ocfs2_dentry_lock *)lockres->l_priv;
}