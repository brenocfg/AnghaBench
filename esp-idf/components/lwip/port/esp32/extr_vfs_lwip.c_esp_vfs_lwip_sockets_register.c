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
struct TYPE_3__ {int /*<<< orphan*/ * stop_socket_select_isr; int /*<<< orphan*/ * stop_socket_select; int /*<<< orphan*/ * get_socket_select_semaphore; int /*<<< orphan*/ * socket_select; int /*<<< orphan*/ * ioctl; int /*<<< orphan*/ * fcntl; int /*<<< orphan*/ * read; int /*<<< orphan*/ * close; int /*<<< orphan*/ * fstat; int /*<<< orphan*/ * open; int /*<<< orphan*/ * write; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ esp_vfs_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_VFS_FLAG_DEFAULT ; 
 int /*<<< orphan*/  LWIP_SOCKET_OFFSET ; 
 int /*<<< orphan*/  MAX_FDS ; 
 int /*<<< orphan*/  esp_vfs_register_fd_range (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwip_close ; 
 int /*<<< orphan*/  lwip_fcntl_r_wrapper ; 
 int /*<<< orphan*/  lwip_get_socket_select_semaphore ; 
 int /*<<< orphan*/  lwip_ioctl_r_wrapper ; 
 int /*<<< orphan*/  lwip_read ; 
 int /*<<< orphan*/  lwip_select ; 
 int /*<<< orphan*/  lwip_stop_socket_select ; 
 int /*<<< orphan*/  lwip_stop_socket_select_isr ; 
 int /*<<< orphan*/  lwip_write ; 

void esp_vfs_lwip_sockets_register(void)
{
    esp_vfs_t vfs = {
        .flags = ESP_VFS_FLAG_DEFAULT,
        .write = &lwip_write,
        .open = NULL,
        .fstat = NULL,
        .close = &lwip_close,
        .read = &lwip_read,
        .fcntl = &lwip_fcntl_r_wrapper,
        .ioctl = &lwip_ioctl_r_wrapper,
        .socket_select = &lwip_select,
        .get_socket_select_semaphore = &lwip_get_socket_select_semaphore,
        .stop_socket_select = &lwip_stop_socket_select,
        .stop_socket_select_isr = &lwip_stop_socket_select_isr,
    };
    /* Non-LWIP file descriptors are from 0 to (LWIP_SOCKET_OFFSET-1). LWIP
     * file descriptors are registered from LWIP_SOCKET_OFFSET to
     * MAX_FDS-1.
     */

    ESP_ERROR_CHECK(esp_vfs_register_fd_range(&vfs, NULL, LWIP_SOCKET_OFFSET, MAX_FDS));
}