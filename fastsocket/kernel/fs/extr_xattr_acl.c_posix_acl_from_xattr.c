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
struct posix_acl_entry {int e_tag; int /*<<< orphan*/  e_id; void* e_perm; } ;
struct posix_acl {struct posix_acl_entry* a_entries; } ;
struct TYPE_3__ {scalar_t__ a_version; } ;
typedef  TYPE_1__ posix_acl_xattr_header ;
struct TYPE_4__ {int /*<<< orphan*/  e_id; int /*<<< orphan*/  e_perm; int /*<<< orphan*/  e_tag; } ;
typedef  TYPE_2__ posix_acl_xattr_entry ;

/* Variables and functions */
#define  ACL_GROUP 133 
#define  ACL_GROUP_OBJ 132 
#define  ACL_MASK 131 
#define  ACL_OTHER 130 
 int /*<<< orphan*/  ACL_UNDEFINED_ID ; 
#define  ACL_USER 129 
#define  ACL_USER_OBJ 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct posix_acl* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  POSIX_ACL_XATTR_VERSION ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct posix_acl* posix_acl_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_xattr_count (size_t) ; 

struct posix_acl *
posix_acl_from_xattr(const void *value, size_t size)
{
	posix_acl_xattr_header *header = (posix_acl_xattr_header *)value;
	posix_acl_xattr_entry *entry = (posix_acl_xattr_entry *)(header+1), *end;
	int count;
	struct posix_acl *acl;
	struct posix_acl_entry *acl_e;

	if (!value)
		return NULL;
	if (size < sizeof(posix_acl_xattr_header))
		 return ERR_PTR(-EINVAL);
	if (header->a_version != cpu_to_le32(POSIX_ACL_XATTR_VERSION))
		return ERR_PTR(-EOPNOTSUPP);

	count = posix_acl_xattr_count(size);
	if (count < 0)
		return ERR_PTR(-EINVAL);
	if (count == 0)
		return NULL;
	
	acl = posix_acl_alloc(count, GFP_NOFS);
	if (!acl)
		return ERR_PTR(-ENOMEM);
	acl_e = acl->a_entries;
	
	for (end = entry + count; entry != end; acl_e++, entry++) {
		acl_e->e_tag  = le16_to_cpu(entry->e_tag);
		acl_e->e_perm = le16_to_cpu(entry->e_perm);

		switch(acl_e->e_tag) {
			case ACL_USER_OBJ:
			case ACL_GROUP_OBJ:
			case ACL_MASK:
			case ACL_OTHER:
				acl_e->e_id = ACL_UNDEFINED_ID;
				break;

			case ACL_USER:
			case ACL_GROUP:
				acl_e->e_id = le32_to_cpu(entry->e_id);
				break;

			default:
				goto fail;
		}
	}
	return acl;

fail:
	posix_acl_release(acl);
	return ERR_PTR(-EINVAL);
}