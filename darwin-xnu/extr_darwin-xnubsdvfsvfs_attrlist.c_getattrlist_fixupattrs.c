#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vnode_attr {int va_active; int va_supported; } ;
struct getattrlist_attrtab {scalar_t__ attr; int bits; } ;
struct TYPE_3__ {int commonattr; int dirattr; int fileattr; int forkattr; } ;
typedef  TYPE_1__ attribute_set_t ;

/* Variables and functions */
 struct getattrlist_attrtab* getattrlist_common_extended_tab ; 
 struct getattrlist_attrtab* getattrlist_common_tab ; 
 struct getattrlist_attrtab* getattrlist_dir_tab ; 
 struct getattrlist_attrtab* getattrlist_file_tab ; 

__attribute__((used)) static void
getattrlist_fixupattrs(attribute_set_t *asp, struct vnode_attr *vap, int use_fork)
{
	struct getattrlist_attrtab *tab;

	if (asp->commonattr) {
		tab = getattrlist_common_tab;
		do {
            /* 
			 * This if() statement is slightly confusing. We're trying to
			 * iterate through all of the bits listed in the array 
			 * getattr_common_tab, and see if the filesystem was expected
			 * to support it, and whether or not we need to do anything about this.
			 * 
			 * This array is full of structs that have 4 fields (attr, bits, size, action).
			 * The first is used to store the ATTR_CMN_* bit that was being requested 
			 * from userland.  The second stores the VATTR_BIT corresponding to the field
			 * filled in vnode_attr struct.  If it is 0, then we don't typically expect
			 * the filesystem to fill in this field.  The third is the size of the field,
			 * and the fourth is the type of kauth actions needed.
			 *
			 * So, for all of the ATTR_CMN bits listed in this array, we iterate through 
			 * them, and check to see if it was both passed down to the filesystem via the
			 * va_active bitfield, and whether or not we expect it to be emitted from
			 * the filesystem.  If it wasn't supported, then we un-twiddle the bit and move
			 * on.  This is done so that we can uncheck those bits and re-request
			 * a vnode_getattr from the filesystem again.
			 */
			if ((tab->attr & asp->commonattr) &&
			    (tab->bits & vap->va_active) &&
			    (tab->bits & vap->va_supported) == 0) {
				asp->commonattr &= ~tab->attr;
			}
		} while ((++tab)->attr != 0);
	}
	if (asp->dirattr) {
		tab = getattrlist_dir_tab;
		do {
			if ((tab->attr & asp->dirattr) &&
			    (tab->bits & vap->va_active) &&
			    (vap->va_supported & tab->bits) == 0) {
				asp->dirattr &= ~tab->attr;
			}
		} while ((++tab)->attr != 0);
	}
	if (asp->fileattr) {
		tab = getattrlist_file_tab;
		do {
			if ((tab->attr & asp->fileattr) &&
			    (tab->bits & vap->va_active) &&
			    (vap->va_supported & tab->bits) == 0) {
				asp->fileattr &= ~tab->attr;
			}
		} while ((++tab)->attr != 0);
	}
	if (use_fork && asp->forkattr) {
		tab = getattrlist_common_extended_tab;
		do {
			if ((tab->attr & asp->forkattr) &&
			    (tab->bits & vap->va_active) &&
			    (vap->va_supported & tab->bits) == 0) {
				asp->forkattr &= ~tab->attr;
			}
		} while ((++tab)->attr != 0);
	}
}