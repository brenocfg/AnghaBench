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
struct sysfs_dirent {int s_ino; char* s_name; TYPE_2__* s_parent; } ;
struct TYPE_3__ {struct dentry* dentry; } ;
struct file {int f_pos; struct sysfs_dirent* private_data; TYPE_1__ f_path; } ;
struct dentry {struct sysfs_dirent* d_fsdata; } ;
typedef  int ino_t ;
typedef  scalar_t__ (* filldir_t ) (void*,char const*,int,int,int,unsigned int) ;
struct TYPE_4__ {int s_ino; } ;

/* Variables and functions */
 unsigned int DT_DIR ; 
 int INT_MAX ; 
 unsigned int dt_type (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 struct sysfs_dirent* sysfs_dir_next_pos (struct sysfs_dirent*,int,struct sysfs_dirent*) ; 
 struct sysfs_dirent* sysfs_dir_pos (struct sysfs_dirent*,int,struct sysfs_dirent*) ; 
 struct sysfs_dirent* sysfs_get (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_mutex ; 

__attribute__((used)) static int sysfs_readdir(struct file * filp, void * dirent, filldir_t filldir)
{
	struct dentry *dentry = filp->f_path.dentry;
	struct sysfs_dirent * parent_sd = dentry->d_fsdata;
	struct sysfs_dirent *pos = filp->private_data;
	ino_t ino;

	if (filp->f_pos == 0) {
		ino = parent_sd->s_ino;
		if (filldir(dirent, ".", 1, filp->f_pos, ino, DT_DIR) == 0)
			filp->f_pos++;
	}
	if (filp->f_pos == 1) {
		if (parent_sd->s_parent)
			ino = parent_sd->s_parent->s_ino;
		else
			ino = parent_sd->s_ino;
		if (filldir(dirent, "..", 2, filp->f_pos, ino, DT_DIR) == 0)
			filp->f_pos++;
	}
	mutex_lock(&sysfs_mutex);
	for (pos = sysfs_dir_pos(parent_sd, filp->f_pos, pos);
	     pos;
	     pos = sysfs_dir_next_pos(parent_sd, filp->f_pos, pos)) {
		const char * name;
		unsigned int type;
		int len, ret;

		name = pos->s_name;
		len = strlen(name);
		ino = pos->s_ino;
		type = dt_type(pos);
		filp->f_pos = ino;
		filp->private_data = sysfs_get(pos);

		mutex_unlock(&sysfs_mutex);
		ret = filldir(dirent, name, len, filp->f_pos, ino, type);
		mutex_lock(&sysfs_mutex);
		if (ret < 0)
			break;
	}
	mutex_unlock(&sysfs_mutex);
	if ((filp->f_pos > 1) && !pos) { /* EOF */
		filp->f_pos = INT_MAX;
		filp->private_data = NULL;
	}
	return 0;
}