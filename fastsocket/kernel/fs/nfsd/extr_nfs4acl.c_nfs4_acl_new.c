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
struct nfs4_acl {scalar_t__ naces; } ;
struct nfs4_ace {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nfs4_acl* kmalloc (int,int /*<<< orphan*/ ) ; 

struct nfs4_acl *
nfs4_acl_new(int n)
{
	struct nfs4_acl *acl;

	acl = kmalloc(sizeof(*acl) + n*sizeof(struct nfs4_ace), GFP_KERNEL);
	if (acl == NULL)
		return NULL;
	acl->naces = 0;
	return acl;
}