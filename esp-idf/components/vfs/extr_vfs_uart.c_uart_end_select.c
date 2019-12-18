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
typedef  int /*<<< orphan*/  uart_select_args_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int UART_NUM ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_get_selectlock () ; 
 int /*<<< orphan*/  uart_set_select_notif_callback (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_select (int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t uart_end_select(void *end_select_args)
{
    uart_select_args_t *args = end_select_args;

    portENTER_CRITICAL(uart_get_selectlock());
    esp_err_t ret = unregister_select(args);
    for (int i = 0; i < UART_NUM; ++i) {
        uart_set_select_notif_callback(i, NULL);
    }
    portEXIT_CRITICAL(uart_get_selectlock());

    if (args) {
        free(args);
    }

    return ret;
}