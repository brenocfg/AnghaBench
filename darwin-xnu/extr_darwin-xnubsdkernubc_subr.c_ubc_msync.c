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
typedef  int /*<<< orphan*/  off_t ;
typedef  int errno_t ;

/* Variables and functions */
 int EINVAL ; 
 int ubc_msync_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*) ; 

errno_t
ubc_msync(vnode_t vp, off_t beg_off, off_t end_off, off_t *resid_off, int flags)
{
        int retval;
	int io_errno = 0;
	
	if (resid_off)
	        *resid_off = beg_off;

        retval = ubc_msync_internal(vp, beg_off, end_off, resid_off, flags, &io_errno);

	if (retval == 0 && io_errno == 0)
	        return (EINVAL);
	return (io_errno);
}