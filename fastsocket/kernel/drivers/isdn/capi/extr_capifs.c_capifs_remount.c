#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int umode_t ;
typedef  int uid_t ;
struct super_block {TYPE_2__* s_root; } ;
typedef  int gid_t ;
struct TYPE_6__ {int setuid; int setgid; int uid; int gid; int mode; } ;
struct TYPE_5__ {TYPE_1__* d_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int S_IFMT ; 
 TYPE_3__ config ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  replace_mount_options (struct super_block*,char*) ; 
 int sscanf (char*,char*,int*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int capifs_remount(struct super_block *s, int *flags, char *data)
{
	int setuid = 0;
	int setgid = 0;
	uid_t uid = 0;
	gid_t gid = 0;
	umode_t mode = 0600;
	char *this_char;
	char *new_opt = kstrdup(data, GFP_KERNEL);

	this_char = NULL;
	while ((this_char = strsep(&data, ",")) != NULL) {
		int n;
		char dummy;
		if (!*this_char)
			continue;
		if (sscanf(this_char, "uid=%i%c", &n, &dummy) == 1) {
			setuid = 1;
			uid = n;
		} else if (sscanf(this_char, "gid=%i%c", &n, &dummy) == 1) {
			setgid = 1;
			gid = n;
		} else if (sscanf(this_char, "mode=%o%c", &n, &dummy) == 1)
			mode = n & ~S_IFMT;
		else {
			kfree(new_opt);
			printk("capifs: called with bogus options\n");
			return -EINVAL;
		}
	}

	mutex_lock(&s->s_root->d_inode->i_mutex);

	replace_mount_options(s, new_opt);
	config.setuid  = setuid;
	config.setgid  = setgid;
	config.uid     = uid;
	config.gid     = gid;
	config.mode    = mode;

	mutex_unlock(&s->s_root->d_inode->i_mutex);

	return 0;
}