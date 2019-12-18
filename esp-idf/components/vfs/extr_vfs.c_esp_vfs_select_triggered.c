#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* stop_socket_select ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_1__ vfs; } ;
typedef  TYPE_2__ vfs_entry_t ;
struct TYPE_8__ {int /*<<< orphan*/  sem; scalar_t__ is_sem_local; } ;
typedef  TYPE_3__ esp_vfs_select_sem_t ;

/* Variables and functions */
 TYPE_2__** s_vfs ; 
 int s_vfs_count ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

void esp_vfs_select_triggered(esp_vfs_select_sem_t sem)
{
    if (sem.is_sem_local) {
        xSemaphoreGive(sem.sem);
    } else {
        // Another way would be to go through s_fd_table and find the VFS
        // which has a permanent FD. But in order to avoid to lock
        // s_fd_table_lock we go through the VFS table.
        for (int i = 0; i < s_vfs_count; ++i) {
            // Note: s_vfs_count could have changed since the start of vfs_select() call. However, that change doesn't
            // matter here stop_socket_select() will be called for only valid VFS drivers.
            const vfs_entry_t *vfs = s_vfs[i];
            if (vfs != NULL && vfs->vfs.stop_socket_select != NULL) {
                vfs->vfs.stop_socket_select(sem.sem);
                break;
            }
        }
    }
}