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
struct ecryptfs_mount_crypt_stat {int dummy; } ;
struct ecryptfs_crypt_stat {struct ecryptfs_mount_crypt_stat* mount_crypt_stat; int /*<<< orphan*/  file_version; int /*<<< orphan*/  flags; int /*<<< orphan*/  key_size; int /*<<< orphan*/  cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECRYPTFS_DEFAULT_CIPHER ; 
 int /*<<< orphan*/  ECRYPTFS_DEFAULT_KEY_BYTES ; 
 int /*<<< orphan*/  ECRYPTFS_FILE_VERSION ; 
 int /*<<< orphan*/  ECRYPTFS_KEY_VALID ; 
 int /*<<< orphan*/  ecryptfs_copy_mount_wide_flags_to_inode_flags (struct ecryptfs_crypt_stat*,struct ecryptfs_mount_crypt_stat*) ; 
 int /*<<< orphan*/  ecryptfs_set_default_sizes (struct ecryptfs_crypt_stat*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecryptfs_set_default_crypt_stat_vals(
	struct ecryptfs_crypt_stat *crypt_stat,
	struct ecryptfs_mount_crypt_stat *mount_crypt_stat)
{
	ecryptfs_copy_mount_wide_flags_to_inode_flags(crypt_stat,
						      mount_crypt_stat);
	ecryptfs_set_default_sizes(crypt_stat);
	strcpy(crypt_stat->cipher, ECRYPTFS_DEFAULT_CIPHER);
	crypt_stat->key_size = ECRYPTFS_DEFAULT_KEY_BYTES;
	crypt_stat->flags &= ~(ECRYPTFS_KEY_VALID);
	crypt_stat->file_version = ECRYPTFS_FILE_VERSION;
	crypt_stat->mount_crypt_stat = mount_crypt_stat;
}