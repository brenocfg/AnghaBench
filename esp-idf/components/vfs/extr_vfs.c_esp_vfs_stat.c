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
struct stat {int dummy; } ;
struct _reent {int dummy; } ;
typedef  int /*<<< orphan*/  __errno_r ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_AND_CALL (int,struct _reent*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*,struct stat*) ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/ * get_vfs_for_path (char const*) ; 
 int /*<<< orphan*/  stat ; 
 char* translate_path (int /*<<< orphan*/  const*,char const*) ; 

int esp_vfs_stat(struct _reent *r, const char * path, struct stat * st)
{
    const vfs_entry_t* vfs = get_vfs_for_path(path);
    if (vfs == NULL) {
        __errno_r(r) = ENOENT;
        return -1;
    }
    const char* path_within_vfs = translate_path(vfs, path);
    int ret;
    CHECK_AND_CALL(ret, r, vfs, stat, path_within_vfs, st);
    return ret;
}