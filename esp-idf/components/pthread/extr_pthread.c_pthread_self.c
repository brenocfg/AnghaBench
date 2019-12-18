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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  esp_pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/ * pthread_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_threads_mux ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 scalar_t__ xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTaskGetCurrentTaskHandle () ; 

pthread_t pthread_self(void)
{
    if (xSemaphoreTake(s_threads_mux, portMAX_DELAY) != pdTRUE) {
        assert(false && "Failed to lock threads list!");
    }
    esp_pthread_t *pthread = pthread_find(xTaskGetCurrentTaskHandle());
    if (!pthread) {
        assert(false && "Failed to find current thread ID!");
    }
    xSemaphoreGive(s_threads_mux);
    return (pthread_t)pthread;
}