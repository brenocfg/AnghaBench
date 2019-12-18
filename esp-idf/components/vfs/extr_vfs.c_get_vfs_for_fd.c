#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_entry_t ;
struct TYPE_2__ {int vfs_index; } ;

/* Variables and functions */
 scalar_t__ fd_valid (int) ; 
 int /*<<< orphan*/ * get_vfs_for_index (int const) ; 
 TYPE_1__* s_fd_table ; 

__attribute__((used)) static const vfs_entry_t *get_vfs_for_fd(int fd)
{
    const vfs_entry_t *vfs = NULL;
    if (fd_valid(fd)) {
        const int index = s_fd_table[fd].vfs_index; // single read -> no locking is required
        vfs = get_vfs_for_index(index);
    }
    return vfs;
}