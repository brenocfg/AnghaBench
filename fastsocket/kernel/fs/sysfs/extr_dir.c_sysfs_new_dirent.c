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
typedef  int /*<<< orphan*/  umode_t ;
struct sysfs_dirent {char const* s_name; int s_flags; int /*<<< orphan*/  s_mode; int /*<<< orphan*/  s_active; int /*<<< orphan*/  s_count; int /*<<< orphan*/  s_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SYSFS_COPY_NAME ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct sysfs_dirent*) ; 
 struct sysfs_dirent* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ sysfs_alloc_ino (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_dir_cachep ; 

struct sysfs_dirent *sysfs_new_dirent(const char *name, umode_t mode, int type)
{
	char *dup_name = NULL;
	struct sysfs_dirent *sd;

	if (type & SYSFS_COPY_NAME) {
		name = dup_name = kstrdup(name, GFP_KERNEL);
		if (!name)
			return NULL;
	}

	sd = kmem_cache_zalloc(sysfs_dir_cachep, GFP_KERNEL);
	if (!sd)
		goto err_out1;

	if (sysfs_alloc_ino(&sd->s_ino))
		goto err_out2;

	atomic_set(&sd->s_count, 1);
	atomic_set(&sd->s_active, 0);

	sd->s_name = name;
	sd->s_mode = mode;
	sd->s_flags = type;

	return sd;

 err_out2:
	kmem_cache_free(sysfs_dir_cachep, sd);
 err_out1:
	kfree(dup_name);
	return NULL;
}