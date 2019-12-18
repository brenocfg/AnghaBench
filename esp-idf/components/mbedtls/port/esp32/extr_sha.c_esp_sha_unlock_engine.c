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
typedef  int /*<<< orphan*/  SemaphoreHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  PERIPH_SHA_MODULE ; 
 scalar_t__ engines_in_use ; 
 int /*<<< orphan*/  engines_in_use_lock ; 
 int /*<<< orphan*/  periph_module_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sha_get_engine_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ *) ; 

void esp_sha_unlock_engine(esp_sha_type sha_type)
{
    SemaphoreHandle_t *engine_state = sha_get_engine_state(sha_type);

    portENTER_CRITICAL(&engines_in_use_lock);

    engines_in_use--;

    if (engines_in_use == 0) {
        /* About to release last engine, so
           disable SHA hardware */
        periph_module_disable(PERIPH_SHA_MODULE);
    }

    portEXIT_CRITICAL(&engines_in_use_lock);

    xSemaphoreGive(engine_state);
}