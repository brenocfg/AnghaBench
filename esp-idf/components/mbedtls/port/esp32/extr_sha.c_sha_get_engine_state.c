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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  esp_sha_type ;
typedef  int /*<<< orphan*/ * SemaphoreHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** engine_states ; 
 unsigned int sha_engine_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uxPortCompareSet (scalar_t__ volatile*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xSemaphoreCreateBinary () ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static SemaphoreHandle_t sha_get_engine_state(esp_sha_type sha_type)
{
    unsigned idx = sha_engine_index(sha_type);
    volatile SemaphoreHandle_t *engine = &engine_states[idx];
    SemaphoreHandle_t result = *engine;
    uint32_t set_engine = 0;

    if (result == NULL) {
        // Create a new semaphore for 'in use' flag
        SemaphoreHandle_t new_engine = xSemaphoreCreateBinary();
        assert(new_engine != NULL);
        xSemaphoreGive(new_engine); // start available

        // try to atomically set the previously NULL *engine to new_engine
        set_engine = (uint32_t)new_engine;
        uxPortCompareSet((volatile uint32_t *)engine, 0, &set_engine);

        if (set_engine != 0) { // we lost a race setting *engine
            vSemaphoreDelete(new_engine);
        }
        result = *engine;
    }
    return result;
}