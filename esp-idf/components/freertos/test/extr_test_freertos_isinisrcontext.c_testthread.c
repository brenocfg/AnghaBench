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
typedef  int /*<<< orphan*/  intr_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  ETS_INTERNAL_TIMER1_INTR_SOURCE ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_HEX32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_intr_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_intr_free (int /*<<< orphan*/ ) ; 
 int in_int_context ; 
 int int_handled ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  testint ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xPortInIsrContext () ; 
 scalar_t__ xthal_get_ccount () ; 
 int /*<<< orphan*/  xthal_set_ccompare (int,scalar_t__) ; 

__attribute__((used)) static void testthread(void *arg) {
    intr_handle_t handle;
    in_int_context=0;
    int_handled=0;
    TEST_ASSERT(!xPortInIsrContext());
    xthal_set_ccompare(1, xthal_get_ccount()+8000000);
    esp_err_t err = esp_intr_alloc(ETS_INTERNAL_TIMER1_INTR_SOURCE, 0, &testint, NULL, &handle);
    TEST_ASSERT_EQUAL_HEX32(ESP_OK, err);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    TEST_ASSERT(int_handled);
    TEST_ASSERT(in_int_context);
    TEST_ASSERT_EQUAL_HEX32( ESP_OK, esp_intr_free(handle) );
    vTaskDelete(NULL);
}