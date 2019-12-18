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
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_INTR_FLAG_INTRDISABLED ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  ETS_INTERNAL_TIMER1_INTR_SOURCE ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 scalar_t__ esp_intr_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_intr_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_intr_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ esp_intr_free (int /*<<< orphan*/ ) ; 
 int esp_intr_get_intno (int /*<<< orphan*/ ) ; 
 int int_timer_ctr ; 
 int /*<<< orphan*/  int_timer_handler ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 scalar_t__ xthal_get_ccount () ; 
 int /*<<< orphan*/  xthal_set_ccompare (int,scalar_t__) ; 

void local_timer_test(void)
{
    intr_handle_t ih;
    esp_err_t r;
    r=esp_intr_alloc(ETS_INTERNAL_TIMER1_INTR_SOURCE, 0, int_timer_handler, NULL, &ih);
    TEST_ASSERT(r==ESP_OK);
    printf("Int timer 1 intno %d\n", esp_intr_get_intno(ih));
    xthal_set_ccompare(1, xthal_get_ccount()+8000000);
    int_timer_ctr=0;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    printf("Timer val after 1 sec: %d\n", int_timer_ctr);
    TEST_ASSERT(int_timer_ctr!=0);
    printf("Disabling int\n");
    esp_intr_disable(ih);
    int_timer_ctr=0;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    printf("Timer val after 1 sec: %d\n", int_timer_ctr);
    TEST_ASSERT(int_timer_ctr==0);
    printf("Re-enabling\n");
    esp_intr_enable(ih);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    printf("Timer val after 1 sec: %d\n", int_timer_ctr);
    TEST_ASSERT(int_timer_ctr!=0);

    printf("Free int, re-alloc disabled\n");
    r=esp_intr_free(ih);
    TEST_ASSERT(r==ESP_OK);
    r=esp_intr_alloc(ETS_INTERNAL_TIMER1_INTR_SOURCE, ESP_INTR_FLAG_INTRDISABLED, int_timer_handler, NULL, &ih);
    TEST_ASSERT(r==ESP_OK);
    int_timer_ctr=0;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    printf("Timer val after 1 sec: %d\n", int_timer_ctr);
    TEST_ASSERT(int_timer_ctr==0);
    printf("Re-enabling\n");
    esp_intr_enable(ih);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    printf("Timer val after 1 sec: %d\n", int_timer_ctr);
    TEST_ASSERT(int_timer_ctr!=0);
    r=esp_intr_free(ih);
    TEST_ASSERT(r==ESP_OK);
    printf("Done.\n");
}