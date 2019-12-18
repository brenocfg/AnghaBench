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
struct TYPE_4__ {int /*<<< orphan*/  dentry; } ;
struct fs_struct {int /*<<< orphan*/  lock; TYPE_1__ pwd; } ;
struct dentry {TYPE_2__* d_inode; } ;
struct cred {int dummy; } ;
struct cachefiles_cache {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {struct fs_struct* fs; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHEFILES_DEAD ; 
 int /*<<< orphan*/  CACHEFILES_READY ; 
 int EINVAL ; 
 int EIO ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cachefiles_begin_secure (struct cachefiles_cache*,struct cred const**) ; 
 int cachefiles_check_in_use (struct cachefiles_cache*,struct dentry*,char*) ; 
 int /*<<< orphan*/  cachefiles_end_secure (struct cachefiles_cache*,struct cred const*) ; 
 TYPE_3__* current ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  kerror (char*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cachefiles_daemon_inuse(struct cachefiles_cache *cache, char *args)
{
	struct fs_struct *fs;
	struct dentry *dir;
	const struct cred *saved_cred;
	int ret;

	//_enter(",%s", args);

	if (strchr(args, '/'))
		goto inval;

	if (!test_bit(CACHEFILES_READY, &cache->flags)) {
		kerror("inuse applied to unready cache");
		return -EIO;
	}

	if (test_bit(CACHEFILES_DEAD, &cache->flags)) {
		kerror("inuse applied to dead cache");
		return -EIO;
	}

	/* extract the directory dentry from the cwd */
	fs = current->fs;
	read_lock(&fs->lock);
	dir = dget(fs->pwd.dentry);
	read_unlock(&fs->lock);

	if (!S_ISDIR(dir->d_inode->i_mode))
		goto notdir;

	cachefiles_begin_secure(cache, &saved_cred);
	ret = cachefiles_check_in_use(cache, dir, args);
	cachefiles_end_secure(cache, saved_cred);

	dput(dir);
	//_leave(" = %d", ret);
	return ret;

notdir:
	dput(dir);
	kerror("inuse command requires dirfd to be a directory");
	return -ENOTDIR;

inval:
	kerror("inuse command requires dirfd and filename");
	return -EINVAL;
}