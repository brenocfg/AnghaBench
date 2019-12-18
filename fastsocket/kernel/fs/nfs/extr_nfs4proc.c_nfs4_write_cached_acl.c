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
struct page {int dummy; } ;
struct nfs4_cached_acl {int cached; size_t len; int /*<<< orphan*/  data; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  _copy_from_pages (int /*<<< orphan*/ ,struct page**,size_t,size_t) ; 
 struct nfs4_cached_acl* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_set_cached_acl (struct inode*,struct nfs4_cached_acl*) ; 

__attribute__((used)) static void nfs4_write_cached_acl(struct inode *inode, struct page **pages, size_t pgbase, size_t acl_len)
{
	struct nfs4_cached_acl *acl;
	size_t buflen = sizeof(*acl) + acl_len;

	if (buflen <= PAGE_SIZE) {
		acl = kmalloc(buflen, GFP_KERNEL);
		if (acl == NULL)
			goto out;
		acl->cached = 1;
		_copy_from_pages(acl->data, pages, pgbase, acl_len);
	} else {
		acl = kmalloc(sizeof(*acl), GFP_KERNEL);
		if (acl == NULL)
			goto out;
		acl->cached = 0;
	}
	acl->len = acl_len;
out:
	nfs4_set_cached_acl(inode, acl);
}