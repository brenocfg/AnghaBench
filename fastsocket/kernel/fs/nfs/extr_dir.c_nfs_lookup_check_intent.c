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
struct nameidata {int flags; } ;

/* Variables and functions */
 int LOOKUP_CONTINUE ; 
 int LOOKUP_PARENT ; 

__attribute__((used)) static inline unsigned int nfs_lookup_check_intent(struct nameidata *nd, unsigned int mask)
{
	if (nd->flags & (LOOKUP_CONTINUE|LOOKUP_PARENT))
		return 0;
	return nd->flags & mask;
}