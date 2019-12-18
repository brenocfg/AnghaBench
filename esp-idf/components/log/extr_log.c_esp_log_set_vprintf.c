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
typedef  int /*<<< orphan*/  vprintf_like_t ;

/* Variables and functions */
 int /*<<< orphan*/  portMAX_DELAY ; 
 scalar_t__ s_log_mutex ; 
 int /*<<< orphan*/  s_log_print_func ; 
 scalar_t__ xSemaphoreCreateMutex () ; 
 int /*<<< orphan*/  xSemaphoreGive (scalar_t__) ; 
 int /*<<< orphan*/  xSemaphoreTake (scalar_t__,int /*<<< orphan*/ ) ; 

vprintf_like_t esp_log_set_vprintf(vprintf_like_t func)
{
    if (!s_log_mutex) {
        s_log_mutex = xSemaphoreCreateMutex();
    }
    xSemaphoreTake(s_log_mutex, portMAX_DELAY);

    vprintf_like_t orig_func = s_log_print_func;
    s_log_print_func = func;

    xSemaphoreGive(s_log_mutex);
    return orig_func;
}