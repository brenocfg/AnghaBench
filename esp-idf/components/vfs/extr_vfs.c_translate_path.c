#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ path_prefix_len; int /*<<< orphan*/  path_prefix; } ;
typedef  TYPE_1__ vfs_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static const char* translate_path(const vfs_entry_t* vfs, const char* src_path)
{
    assert(strncmp(src_path, vfs->path_prefix, vfs->path_prefix_len) == 0);
    if (strlen(src_path) == vfs->path_prefix_len) {
        // special case when src_path matches the path prefix exactly
        return "/";
    }
    return src_path + vfs->path_prefix_len;
}