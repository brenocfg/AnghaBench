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
typedef  int /*<<< orphan*/  esp_event_loop_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  esp_event_loop_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 

__attribute__((used)) static void loop_run_task(void* args)
{
    esp_event_loop_handle_t event_loop = (esp_event_loop_handle_t) args;

    while(1) {
        esp_event_loop_run(event_loop, portMAX_DELAY);
    }
}