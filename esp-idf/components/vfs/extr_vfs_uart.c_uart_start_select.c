#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void** readfds; void** writefds; void** errorfds; int /*<<< orphan*/  select_sem; void* readfds_orig; void* errorfds_orig; void* writefds_orig; } ;
typedef  TYPE_1__ uart_select_args_t ;
typedef  void* fd_set ;
typedef  int /*<<< orphan*/  esp_vfs_select_sem_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_NO_MEM ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ FD_ISSET (int,void**) ; 
 int /*<<< orphan*/  FD_SET (int,void**) ; 
 int /*<<< orphan*/  FD_ZERO (void**) ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_NUM ; 
 int /*<<< orphan*/  esp_vfs_select_triggered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ ) ; 
 scalar_t__ register_select (TYPE_1__*) ; 
 int /*<<< orphan*/  select_notif_callback_isr ; 
 scalar_t__ uart_get_buffered_data_len (int,size_t*) ; 
 int /*<<< orphan*/  uart_get_selectlock () ; 
 int /*<<< orphan*/  uart_set_select_notif_callback (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t uart_start_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
        esp_vfs_select_sem_t select_sem, void **end_select_args)
{
    const int max_fds = MIN(nfds, UART_NUM);
    *end_select_args = NULL;

    uart_select_args_t *args = malloc(sizeof(uart_select_args_t));

    if (args == NULL) {
        return ESP_ERR_NO_MEM;
    }

    args->select_sem = select_sem;
    args->readfds = readfds;
    args->writefds = writefds;
    args->errorfds = exceptfds;
    args->readfds_orig = *readfds; // store the original values because they will be set to zero
    args->writefds_orig = *writefds;
    args->errorfds_orig = *exceptfds;
    FD_ZERO(readfds);
    FD_ZERO(writefds);
    FD_ZERO(exceptfds);

    portENTER_CRITICAL(uart_get_selectlock());

    //uart_set_select_notif_callback sets the callbacks in UART ISR
    for (int i = 0; i < max_fds; ++i) {
        if (FD_ISSET(i, &args->readfds_orig) || FD_ISSET(i, &args->writefds_orig) || FD_ISSET(i, &args->errorfds_orig)) {
            uart_set_select_notif_callback(i, select_notif_callback_isr);
        }
    }

    for (int i = 0; i < max_fds; ++i) {
        if (FD_ISSET(i, &args->readfds_orig)) {
            size_t buffered_size;
            if (uart_get_buffered_data_len(i, &buffered_size) == ESP_OK && buffered_size > 0) {
                // signalize immediately when data is buffered
                FD_SET(i, readfds);
                esp_vfs_select_triggered(args->select_sem);
            }
        }
    }

    esp_err_t ret = register_select(args);
    if (ret != ESP_OK) {
        portEXIT_CRITICAL(uart_get_selectlock());
        free(args);
        return ret;
    }

    portEXIT_CRITICAL(uart_get_selectlock());

    *end_select_args = args;
    return ESP_OK;
}