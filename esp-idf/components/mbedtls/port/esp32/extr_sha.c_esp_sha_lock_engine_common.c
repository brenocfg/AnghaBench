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
typedef  int /*<<< orphan*/  esp_sha_type ;
typedef  int /*<<< orphan*/  TickType_t ;
typedef  int /*<<< orphan*/  SemaphoreHandle_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  PERIPH_SHA_MODULE ; 
 int /*<<< orphan*/  assert (int) ; 
 int engines_in_use ; 
 int /*<<< orphan*/  engines_in_use_lock ; 
 scalar_t__ pdFALSE ; 
 int /*<<< orphan*/  periph_module_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha_get_engine_state (int /*<<< orphan*/ ) ; 
 scalar_t__ xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool esp_sha_lock_engine_common(esp_sha_type sha_type, TickType_t ticks_to_wait)
{
    SemaphoreHandle_t engine_state = sha_get_engine_state(sha_type);
    BaseType_t result = xSemaphoreTake(engine_state, ticks_to_wait);

    if (result == pdFALSE) {
        // failed to take semaphore
        return false;
    }

    portENTER_CRITICAL(&engines_in_use_lock);

    if (engines_in_use == 0) {
        /* Just locked first engine,
           so enable SHA hardware */
        periph_module_enable(PERIPH_SHA_MODULE);
    }

    engines_in_use++;
    assert(engines_in_use <= 3);

    portEXIT_CRITICAL(&engines_in_use_lock);

    return true;
}