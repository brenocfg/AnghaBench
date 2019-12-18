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
typedef  int xfs_km_flags_t ;
typedef  int gfp_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int GFP_ATOMIC ; 
 int GFP_KERNEL ; 
 int KM_MAYFAIL ; 
 int KM_NOFS ; 
 int KM_NOSLEEP ; 
 int KM_SLEEP ; 
 int PF_FSTRANS ; 
 int __GFP_FS ; 
 int __GFP_NOWARN ; 
 TYPE_1__* current ; 

__attribute__((used)) static inline gfp_t
kmem_flags_convert(xfs_km_flags_t flags)
{
	gfp_t	lflags;

	BUG_ON(flags & ~(KM_SLEEP|KM_NOSLEEP|KM_NOFS|KM_MAYFAIL));

	if (flags & KM_NOSLEEP) {
		lflags = GFP_ATOMIC | __GFP_NOWARN;
	} else {
		lflags = GFP_KERNEL | __GFP_NOWARN;
		if ((current->flags & PF_FSTRANS) || (flags & KM_NOFS))
			lflags &= ~__GFP_FS;
	}
	return lflags;
}