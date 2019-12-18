#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct posix_acl {TYPE_1__* a_entries; } ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int e_perm; void* e_id; int /*<<< orphan*/  e_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_GROUP_OBJ ; 
 int /*<<< orphan*/  ACL_OTHER ; 
 void* ACL_UNDEFINED_ID ; 
 int /*<<< orphan*/  ACL_USER_OBJ ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct posix_acl* ERR_PTR (int /*<<< orphan*/ ) ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 struct posix_acl* posix_acl_alloc (int,int /*<<< orphan*/ ) ; 

struct posix_acl *
posix_acl_from_mode(mode_t mode, gfp_t flags)
{
	struct posix_acl *acl = posix_acl_alloc(3, flags);
	if (!acl)
		return ERR_PTR(-ENOMEM);

	acl->a_entries[0].e_tag  = ACL_USER_OBJ;
	acl->a_entries[0].e_id   = ACL_UNDEFINED_ID;
	acl->a_entries[0].e_perm = (mode & S_IRWXU) >> 6;

	acl->a_entries[1].e_tag  = ACL_GROUP_OBJ;
	acl->a_entries[1].e_id   = ACL_UNDEFINED_ID;
	acl->a_entries[1].e_perm = (mode & S_IRWXG) >> 3;

	acl->a_entries[2].e_tag  = ACL_OTHER;
	acl->a_entries[2].e_id   = ACL_UNDEFINED_ID;
	acl->a_entries[2].e_perm = (mode & S_IRWXO);
	return acl;
}