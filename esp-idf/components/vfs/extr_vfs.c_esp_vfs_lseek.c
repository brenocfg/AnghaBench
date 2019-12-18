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
typedef  int /*<<< orphan*/  vfs_entry_t ;
struct _reent {int dummy; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  __errno_r ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_AND_CALL (int,struct _reent*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int const,int,int) ; 
 int /*<<< orphan*/  EBADF ; 
 int get_local_fd (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * get_vfs_for_fd (int) ; 
 int /*<<< orphan*/  lseek ; 

off_t esp_vfs_lseek(struct _reent *r, int fd, off_t size, int mode)
{
    const vfs_entry_t* vfs = get_vfs_for_fd(fd);
    const int local_fd = get_local_fd(vfs, fd);
    if (vfs == NULL || local_fd < 0) {
        __errno_r(r) = EBADF;
        return -1;
    }
    off_t ret;
    CHECK_AND_CALL(ret, r, vfs, lseek, local_fd, size, mode);
    return ret;
}