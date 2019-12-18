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
struct xdr_array2_desc {int dummy; } ;
struct posix_acl_entry {int e_tag; int e_id; int e_perm; } ;
struct nfsacl_encode_desc {int typeflag; int uid; int gid; int /*<<< orphan*/  count; TYPE_1__* acl; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct posix_acl_entry* a_entries; } ;

/* Variables and functions */
#define  ACL_GROUP 131 
#define  ACL_GROUP_OBJ 130 
#define  ACL_USER 129 
#define  ACL_USER_OBJ 128 
 int S_IRWXO ; 
 void* htonl (int) ; 

__attribute__((used)) static int
xdr_nfsace_encode(struct xdr_array2_desc *desc, void *elem)
{
	struct nfsacl_encode_desc *nfsacl_desc =
		(struct nfsacl_encode_desc *) desc;
	__be32 *p = elem;

	struct posix_acl_entry *entry =
		&nfsacl_desc->acl->a_entries[nfsacl_desc->count++];

	*p++ = htonl(entry->e_tag | nfsacl_desc->typeflag);
	switch(entry->e_tag) {
		case ACL_USER_OBJ:
			*p++ = htonl(nfsacl_desc->uid);
			break;
		case ACL_GROUP_OBJ:
			*p++ = htonl(nfsacl_desc->gid);
			break;
		case ACL_USER:
		case ACL_GROUP:
			*p++ = htonl(entry->e_id);
			break;
		default:  /* Solaris depends on that! */
			*p++ = 0;
			break;
	}
	*p++ = htonl(entry->e_perm & S_IRWXO);
	return 0;
}