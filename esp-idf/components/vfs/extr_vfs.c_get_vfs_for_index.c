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

/* Variables and functions */
 int /*<<< orphan*/  const** s_vfs ; 
 int s_vfs_count ; 

__attribute__((used)) static inline const vfs_entry_t *get_vfs_for_index(int index)
{
    if (index < 0 || index >= s_vfs_count) {
        return NULL;
    } else {
        return s_vfs[index];
    }
}