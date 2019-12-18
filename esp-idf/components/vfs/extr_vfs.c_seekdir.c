#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_entry_t ;
struct _reent {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dd_vfs_idx; } ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_AND_CALLV (struct _reent*,int /*<<< orphan*/  const*,void (*) (TYPE_1__*,long),TYPE_1__*,long) ; 
 int /*<<< orphan*/  EBADF ; 
 struct _reent* __getreent () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * get_vfs_for_index (int /*<<< orphan*/ ) ; 

void seekdir(DIR* pdir, long loc)
{
    const vfs_entry_t* vfs = get_vfs_for_index(pdir->dd_vfs_idx);
    struct _reent* r = __getreent();
    if (vfs == NULL) {
        errno = EBADF;
        return;
    }
    CHECK_AND_CALLV(r, vfs, seekdir, pdir, loc);
}