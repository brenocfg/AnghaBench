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
struct readlink_args {int /*<<< orphan*/  count; int /*<<< orphan*/  buf; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  CAST_USER_ADDR_T (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_64BIT_PROCESS (int /*<<< orphan*/ ) ; 
 int UIO_USERSPACE32 ; 
 int UIO_USERSPACE64 ; 
 int readlinkat_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_context_current () ; 

int
readlink(proc_t p, struct readlink_args *uap, int32_t *retval)
{
	enum uio_seg procseg;

	procseg = IS_64BIT_PROCESS(p) ? UIO_USERSPACE64 : UIO_USERSPACE32;
	return (readlinkat_internal(vfs_context_current(), AT_FDCWD,
	    CAST_USER_ADDR_T(uap->path), procseg, CAST_USER_ADDR_T(uap->buf),
	    uap->count, procseg, retval));
}