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
struct componentname {int cn_flags; } ;
struct nameidata {int ni_flag; struct componentname ni_cnd; } ;

/* Variables and functions */
 int ENOENT ; 
 int EROFS ; 
 int ISLASTCN ; 
 int NAMEI_TRAILINGSLASH ; 
 int RDONLY ; 
 int WILLBEDIR ; 

int 
lookup_validate_creation_path(struct nameidata *ndp)
{
	struct componentname *cnp = &ndp->ni_cnd;

	/*
	 * If creating and at end of pathname, then can consider
	 * allowing file to be created.
	 */
	if (cnp->cn_flags & RDONLY) {
		return EROFS;
	}
	if ((cnp->cn_flags & ISLASTCN) && (ndp->ni_flag & NAMEI_TRAILINGSLASH) && !(cnp->cn_flags & WILLBEDIR)) {
		return ENOENT;
	}
	
	return 0;
}