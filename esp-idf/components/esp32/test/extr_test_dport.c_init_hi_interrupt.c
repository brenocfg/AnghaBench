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

/* Variables and functions */
 int ESP_INTR_FLAG_IRAM ; 
 int ESP_INTR_FLAG_LEVEL5 ; 
 int /*<<< orphan*/  ETS_INTERNAL_TIMER2_INTR_SOURCE ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_intr_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_intr_free (int /*<<< orphan*/ ) ; 
 int exit_flag ; 
 int /*<<< orphan*/  inth ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int xPortGetCoreID () ; 

__attribute__((used)) static void init_hi_interrupt(void *arg)
{
    printf("init hi_interrupt on CPU%d \n", xPortGetCoreID());
    TEST_ESP_OK(esp_intr_alloc(ETS_INTERNAL_TIMER2_INTR_SOURCE, ESP_INTR_FLAG_LEVEL5 | ESP_INTR_FLAG_IRAM, NULL, NULL, &inth));
    while (exit_flag == false);
    esp_intr_free(inth);
    printf("disable hi_interrupt on CPU%d \n", xPortGetCoreID());
    vTaskDelete(NULL);
}