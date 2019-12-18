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
struct inode {int dummy; } ;
struct TYPE_8__ {TYPE_2__* dentry; } ;
struct file {TYPE_3__ f_path; } ;
struct TYPE_6__ {unsigned char const* name; } ;
struct TYPE_10__ {TYPE_1__ d_name; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_4__ d_name; TYPE_5__* d_parent; } ;

/* Variables and functions */
 int EREMOTE ; 
 int /*<<< orphan*/  _enter (char*,struct inode*,struct file*,TYPE_5__*,unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afs_mntpt_open(struct inode *inode, struct file *file)
{
	_enter("%p,%p{%p{%s},%s}",
	       inode, file,
	       file->f_path.dentry->d_parent,
	       file->f_path.dentry->d_parent ?
	       file->f_path.dentry->d_parent->d_name.name :
	       (const unsigned char *) "",
	       file->f_path.dentry->d_name.name);

	return -EREMOTE;
}