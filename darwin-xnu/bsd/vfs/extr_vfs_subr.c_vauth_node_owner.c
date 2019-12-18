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
struct vnode_attr {scalar_t__ va_uid; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 scalar_t__ VATTR_IS_SUPPORTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_uid ; 

__attribute__((used)) static int
vauth_node_owner(struct vnode_attr *vap, kauth_cred_t cred)
{
	int result;

	/* default assumption is not-owner */
	result = 0;

	/*
	 * If the filesystem has given us a UID, we treat this as authoritative.
	 */
	if (vap && VATTR_IS_SUPPORTED(vap, va_uid)) {
		result = (vap->va_uid == kauth_cred_getuid(cred)) ? 1 : 0;
	}
	/* we could test the owner UUID here if we had a policy for it */
	
	return(result);
}