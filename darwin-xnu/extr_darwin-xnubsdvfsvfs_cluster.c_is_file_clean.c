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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ PAGE_SIZE_64 ; 
 int UPL_POP_DIRTY ; 
 scalar_t__ ubc_page_op (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

int
is_file_clean(vnode_t vp, off_t filesize)
{
        off_t f_offset;
	int   flags;
	int   total_dirty = 0;

	for (f_offset = 0; f_offset < filesize; f_offset += PAGE_SIZE_64) {
	        if (ubc_page_op(vp, f_offset, 0, NULL, &flags) == KERN_SUCCESS) {
		        if (flags & UPL_POP_DIRTY) {
			        total_dirty++;
			}
		}
	}
	if (total_dirty)
	        return(EINVAL);

	return (0);
}