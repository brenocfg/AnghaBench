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
struct vnode_attr {int va_flags; } ;

/* Variables and functions */
 int APPEND ; 
 int EPERM ; 
 int IMMUTABLE ; 
 int /*<<< orphan*/  KAUTH_DEBUG (char*,int,int,int,int) ; 
 int UF_APPEND ; 
 int UF_IMMUTABLE ; 
 scalar_t__ securelevel ; 

__attribute__((used)) static int
vnode_immutable(struct vnode_attr *vap, int append, int ignore)
{
	int	mask;

	/* start with all bits precluding the operation */
	mask = IMMUTABLE | APPEND;

	/* if appending only, remove the append-only bits */
	if (append)
		mask &= ~APPEND;

	/* ignore only set when authorizing flags changes */
	if (ignore) {
		if (securelevel <= 0) {
			/* in insecure state, flags do not inhibit changes */
			mask = 0;
		} else {
			/* in secure state, user flags don't inhibit */
			mask &= ~(UF_IMMUTABLE | UF_APPEND);
		}
	}
	KAUTH_DEBUG("IMMUTABLE - file flags 0x%x mask 0x%x append = %d ignore = %d", vap->va_flags, mask, append, ignore);
	if ((vap->va_flags & mask) != 0)
		return(EPERM);
	return(0);
}