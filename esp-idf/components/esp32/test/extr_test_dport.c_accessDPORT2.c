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
typedef  int /*<<< orphan*/  xSemaphoreHandle ;

/* Variables and functions */
 int /*<<< orphan*/  DPORT_DATE_REG ; 
 scalar_t__ DPORT_REG_READ (int /*<<< orphan*/ ) ; 
 int ESP_INTR_FLAG_IRAM ; 
 int ESP_INTR_FLAG_LEVEL5 ; 
 int /*<<< orphan*/  ETS_INTERNAL_TIMER2_INTR_SOURCE ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 scalar_t__ XTHAL_GET_CCOUNT () ; 
 int /*<<< orphan*/  XTHAL_SET_CCOMPARE (int,scalar_t__) ; 
 int dport_test_result ; 
 int /*<<< orphan*/  esp_intr_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_intr_free (int /*<<< orphan*/ ) ; 
 int exit_flag ; 
 int /*<<< orphan*/  inth ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void accessDPORT2(void *pvParameters)
{
    xSemaphoreHandle *sema = (xSemaphoreHandle *) pvParameters;
    dport_test_result = true;

    TEST_ESP_OK(esp_intr_alloc(ETS_INTERNAL_TIMER2_INTR_SOURCE, ESP_INTR_FLAG_LEVEL5 | ESP_INTR_FLAG_IRAM, NULL, NULL, &inth));

    while (exit_flag == false) {
        XTHAL_SET_CCOMPARE(2, XTHAL_GET_CCOUNT() + 21);
        for (int i = 0; i < 200; ++i) {
            if (DPORT_REG_READ(DPORT_DATE_REG) != DPORT_REG_READ(DPORT_DATE_REG)) {
                dport_test_result = false;
                break;
            }
        }
    }
    esp_intr_free(inth);
    printf("accessDPORT2 finish\n");

    xSemaphoreGive(*sema);
    vTaskDelete(NULL);
}