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
struct stat {int st_mode; } ;
typedef  int /*<<< orphan*/ * acl_t ;
typedef  int /*<<< orphan*/  acl_permset_t ;
typedef  int /*<<< orphan*/  acl_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_EXECUTE ; 
 int /*<<< orphan*/  ACL_GROUP_OBJ ; 
 int /*<<< orphan*/  ACL_OTHER ; 
 int /*<<< orphan*/  ACL_READ ; 
 int /*<<< orphan*/  ACL_USER_OBJ ; 
 int /*<<< orphan*/  ACL_WRITE ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int acl_add_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int acl_clear_perms (int /*<<< orphan*/ ) ; 
 int acl_create_entry (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int acl_get_permset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * acl_init (int) ; 
 int acl_set_permset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int acl_set_tag_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acl_t
acl_from_stat(const struct stat *sb)
{
	acl_t acl;
	acl_entry_t entry;
	acl_permset_t perms;

	/* create the ACL */
	acl = acl_init(3);
	if (!acl)
		return NULL;

	/* First entry: ACL_USER_OBJ */
	if (acl_create_entry(&acl, &entry) == -1)
		return NULL;
	if (acl_set_tag_type(entry, ACL_USER_OBJ) == -1)
		return NULL;

	if (acl_get_permset(entry, &perms) == -1)
		return NULL;
	if (acl_clear_perms(perms) == -1)
		return NULL;

	/* calculate user mode */
	if (sb->st_mode & S_IRUSR)
		if (acl_add_perm(perms, ACL_READ) == -1)
			return NULL;
	if (sb->st_mode & S_IWUSR)
		if (acl_add_perm(perms, ACL_WRITE) == -1)
			return NULL;
	if (sb->st_mode & S_IXUSR)
		if (acl_add_perm(perms, ACL_EXECUTE) == -1)
			return NULL;
	if (acl_set_permset(entry, perms) == -1)
		return NULL;

	/* Second entry: ACL_GROUP_OBJ */
	if (acl_create_entry(&acl, &entry) == -1)
		return NULL;
	if (acl_set_tag_type(entry, ACL_GROUP_OBJ) == -1)
		return NULL;

	if (acl_get_permset(entry, &perms) == -1)
		return NULL;
	if (acl_clear_perms(perms) == -1)
		return NULL;

	/* calculate group mode */
	if (sb->st_mode & S_IRGRP)
		if (acl_add_perm(perms, ACL_READ) == -1)
			return NULL;
	if (sb->st_mode & S_IWGRP)
		if (acl_add_perm(perms, ACL_WRITE) == -1)
			return NULL;
	if (sb->st_mode & S_IXGRP)
		if (acl_add_perm(perms, ACL_EXECUTE) == -1)
			return NULL;
	if (acl_set_permset(entry, perms) == -1)
		return NULL;

	/* Third entry: ACL_OTHER */
	if (acl_create_entry(&acl, &entry) == -1)
		return NULL;
	if (acl_set_tag_type(entry, ACL_OTHER) == -1)
		return NULL;

	if (acl_get_permset(entry, &perms) == -1)
		return NULL;
	if (acl_clear_perms(perms) == -1)
		return NULL;

	/* calculate other mode */
	if (sb->st_mode & S_IROTH)
		if (acl_add_perm(perms, ACL_READ) == -1)
			return NULL;
	if (sb->st_mode & S_IWOTH)
		if (acl_add_perm(perms, ACL_WRITE) == -1)
			return NULL;
	if (sb->st_mode & S_IXOTH)
		if (acl_add_perm(perms, ACL_EXECUTE) == -1)
			return NULL;
	if (acl_set_permset(entry, perms) == -1)
		return NULL;

	return(acl);
}