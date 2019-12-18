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
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** realloc (int /*<<< orphan*/ **,int const) ; 
 int /*<<< orphan*/  s_registered_select_lock ; 
 int s_registered_select_num ; 
 int /*<<< orphan*/ ** s_registered_selects ; 

__attribute__((used)) static esp_err_t unregister_select(uart_select_args_t *args)
{
    esp_err_t ret = ESP_OK;
    if (args) {
        ret = ESP_ERR_INVALID_STATE;
        portENTER_CRITICAL(&s_registered_select_lock);
        for (int i = 0; i < s_registered_select_num; ++i) {
            if (s_registered_selects[i] == args) {
                const int new_size = s_registered_select_num - 1;
                // The item is removed by overwriting it with the last item. The subsequent rellocation will drop the
                // last item.
                s_registered_selects[i] = s_registered_selects[new_size];
                s_registered_selects = realloc(s_registered_selects, new_size * sizeof(uart_select_args_t *));
                if (s_registered_selects || new_size == 0) {
                    s_registered_select_num = new_size;
                    ret = ESP_OK;
                } else {
                    ret = ESP_ERR_NO_MEM;
                }
                break;
            }
        }
        portEXIT_CRITICAL(&s_registered_select_lock);
    }
    return ret;
}