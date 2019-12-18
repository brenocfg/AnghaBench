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
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  path_stat ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

int64_t mz_os_get_file_size(const char *path)
{
    struct stat path_stat;

    memset(&path_stat, 0, sizeof(path_stat));
    if (stat(path, &path_stat) == 0)
    {
        /* Stat returns size taken up by directory entry, so return 0 */
        if (S_ISDIR(path_stat.st_mode))
            return 0;

        return path_stat.st_size;
    }

    return 0;
}