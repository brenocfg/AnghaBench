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
typedef  int /*<<< orphan*/  __errno_r ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_AND_CALL (int,struct _reent*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  EXDEV ; 
 int /*<<< orphan*/ * get_vfs_for_path (char const*) ; 
 int /*<<< orphan*/  rename ; 
 char* translate_path (int /*<<< orphan*/  const*,char const*) ; 

int esp_vfs_rename(struct _reent *r, const char *src, const char *dst)
{
    const vfs_entry_t* vfs = get_vfs_for_path(src);
    if (vfs == NULL) {
        __errno_r(r) = ENOENT;
        return -1;
    }
    const vfs_entry_t* vfs_dst = get_vfs_for_path(dst);
    if (vfs != vfs_dst) {
        __errno_r(r) = EXDEV;
        return -1;
    }
    const char* src_within_vfs = translate_path(vfs, src);
    const char* dst_within_vfs = translate_path(vfs, dst);
    int ret;
    CHECK_AND_CALL(ret, r, vfs, rename, src_within_vfs, dst_within_vfs);
    return ret;
}