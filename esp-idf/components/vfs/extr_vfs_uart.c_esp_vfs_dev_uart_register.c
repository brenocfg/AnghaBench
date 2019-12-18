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
struct TYPE_3__ {int /*<<< orphan*/ * tcflush; int /*<<< orphan*/ * tcdrain; int /*<<< orphan*/ * tcgetattr; int /*<<< orphan*/ * tcsetattr; int /*<<< orphan*/ * end_select; int /*<<< orphan*/ * start_select; int /*<<< orphan*/ * access; int /*<<< orphan*/ * fsync; int /*<<< orphan*/ * fcntl; int /*<<< orphan*/ * read; int /*<<< orphan*/ * close; int /*<<< orphan*/ * fstat; int /*<<< orphan*/ * open; int /*<<< orphan*/ * write; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ esp_vfs_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_VFS_FLAG_DEFAULT ; 
 int /*<<< orphan*/  esp_vfs_register (char*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_access ; 
 int /*<<< orphan*/  uart_close ; 
 int /*<<< orphan*/  uart_end_select ; 
 int /*<<< orphan*/  uart_fcntl ; 
 int /*<<< orphan*/  uart_fstat ; 
 int /*<<< orphan*/  uart_fsync ; 
 int /*<<< orphan*/  uart_open ; 
 int /*<<< orphan*/  uart_read ; 
 int /*<<< orphan*/  uart_start_select ; 
 int /*<<< orphan*/  uart_tcdrain ; 
 int /*<<< orphan*/  uart_tcflush ; 
 int /*<<< orphan*/  uart_tcgetattr ; 
 int /*<<< orphan*/  uart_tcsetattr ; 
 int /*<<< orphan*/  uart_write ; 

void esp_vfs_dev_uart_register(void)
{
    esp_vfs_t vfs = {
        .flags = ESP_VFS_FLAG_DEFAULT,
        .write = &uart_write,
        .open = &uart_open,
        .fstat = &uart_fstat,
        .close = &uart_close,
        .read = &uart_read,
        .fcntl = &uart_fcntl,
        .fsync = &uart_fsync,
        .access = &uart_access,
        .start_select = &uart_start_select,
        .end_select = &uart_end_select,
#ifdef CONFIG_VFS_SUPPORT_TERMIOS
        .tcsetattr = &uart_tcsetattr,
        .tcgetattr = &uart_tcgetattr,
        .tcdrain = &uart_tcdrain,
        .tcflush = &uart_tcflush,
#endif // CONFIG_VFS_SUPPORT_TERMIOS
    };
    ESP_ERROR_CHECK(esp_vfs_register("/dev/uart", &vfs, NULL));
}