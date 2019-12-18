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
struct TYPE_3__ {int /*<<< orphan*/  target_sd; } ;
struct sysfs_dirent {int /*<<< orphan*/  s_count; int /*<<< orphan*/  s_ino; TYPE_2__* s_iattr; TYPE_2__* s_name; TYPE_1__ s_symlink; struct sysfs_dirent* s_parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  ia_secdata_len; scalar_t__ ia_secdata; } ;

/* Variables and functions */
 int SYSFS_COPY_NAME ; 
 int SYSFS_KOBJ_LINK ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct sysfs_dirent*) ; 
 int /*<<< orphan*/  security_release_secctx (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_dir_cachep ; 
 int /*<<< orphan*/  sysfs_free_ino (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_put (int /*<<< orphan*/ ) ; 
 int sysfs_type (struct sysfs_dirent*) ; 

void release_sysfs_dirent(struct sysfs_dirent * sd)
{
	struct sysfs_dirent *parent_sd;

 repeat:
	/* Moving/renaming is always done while holding reference.
	 * sd->s_parent won't change beneath us.
	 */
	parent_sd = sd->s_parent;

	if (sysfs_type(sd) == SYSFS_KOBJ_LINK)
		sysfs_put(sd->s_symlink.target_sd);
	if (sysfs_type(sd) & SYSFS_COPY_NAME)
		kfree(sd->s_name);
	if (sd->s_iattr && sd->s_iattr->ia_secdata)
		security_release_secctx(sd->s_iattr->ia_secdata,
					sd->s_iattr->ia_secdata_len);
	kfree(sd->s_iattr);
	sysfs_free_ino(sd->s_ino);
	kmem_cache_free(sysfs_dir_cachep, sd);

	sd = parent_sd;
	if (sd && atomic_dec_and_test(&sd->s_count))
		goto repeat;
}