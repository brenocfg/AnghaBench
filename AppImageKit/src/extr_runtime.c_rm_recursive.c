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

/* Variables and functions */
 int FTW_DEPTH ; 
 int FTW_MOUNT ; 
 int FTW_PHYS ; 
 int nftw (char const* const,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rm_recursive_callback ; 

bool rm_recursive(const char* const path) {
    // FTW_DEPTH: perform depth-first search to make sure files are deleted before the containing directories
    // FTW_MOUNT: prevent deletion of files on other mounted filesystems
    // FTW_PHYS: do not follow symlinks, but report symlinks as such; this way, the symlink targets, which might point
    //           to locations outside path will not be deleted accidentally (attackers might abuse this)
    int rv = nftw(path, &rm_recursive_callback, 0, FTW_DEPTH | FTW_MOUNT | FTW_PHYS);

    return rv == 0;
}