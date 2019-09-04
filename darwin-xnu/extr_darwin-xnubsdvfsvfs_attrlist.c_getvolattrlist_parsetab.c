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
struct vfs_attr {int /*<<< orphan*/  f_active; } ;
struct user64_timespec {int dummy; } ;
struct user32_timespec {int dummy; } ;
struct getvolattrlist_attrtab {scalar_t__ attr; scalar_t__ size; int /*<<< orphan*/  bits; } ;
typedef  int ssize_t ;
typedef  int attrgroup_t ;

/* Variables and functions */
 scalar_t__ ATTR_TIME_SIZE ; 
 int EINVAL ; 

__attribute__((used)) static int
getvolattrlist_parsetab(struct getvolattrlist_attrtab *tab, attrgroup_t attrs, struct vfs_attr *vsp,
		ssize_t *sizep, int is_64bit, unsigned int maxiter)
{
	attrgroup_t	recognised;

	recognised = 0;
	do {
		/* is this attribute set? */
		if (tab->attr & attrs) {
			recognised |= tab->attr;
			vsp->f_active |= tab->bits;
			if (tab->size == ATTR_TIME_SIZE) {
				if (is_64bit) {
					*sizep += sizeof(struct user64_timespec);
				} else {
					*sizep += sizeof(struct user32_timespec);
				}
			} else {
				*sizep += tab->size;
			}
		}
	} while (((++tab)->attr != 0) && (--maxiter > 0));
	
	/* check to make sure that we recognised all of the passed-in attributes */
	if (attrs & ~recognised)
		return(EINVAL);
	return(0);
}