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
typedef  int /*<<< orphan*/  timer_isr_handle_t ;

/* Variables and functions */
 int ESP_INTR_FLAG_INTRDISABLED ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TIMER_0 ; 
 int /*<<< orphan*/  TIMER_1 ; 
 int /*<<< orphan*/  TIMER_GROUP_0 ; 
 int /*<<< orphan*/  TIMER_GROUP_1 ; 
 int* count ; 
 int /*<<< orphan*/  esp_intr_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_intr_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_intr_free (int /*<<< orphan*/ ) ; 
 int esp_intr_get_intno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_timer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  timer_isr ; 
 int /*<<< orphan*/  timer_isr_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void timer_test(int flags) {
    int x;
    timer_isr_handle_t inth[4];
    my_timer_init(TIMER_GROUP_0, TIMER_0, 110000);
    my_timer_init(TIMER_GROUP_0, TIMER_1, 120000);
    my_timer_init(TIMER_GROUP_1, TIMER_0, 130000);
    my_timer_init(TIMER_GROUP_1, TIMER_1, 140000);
    timer_isr_register(TIMER_GROUP_0, TIMER_0, timer_isr, (void*)0, flags|ESP_INTR_FLAG_INTRDISABLED, &inth[0]);
    timer_isr_register(TIMER_GROUP_0, TIMER_1, timer_isr, (void*)1, flags, &inth[1]);
    timer_isr_register(TIMER_GROUP_1, TIMER_0, timer_isr, (void*)2, flags, &inth[2]);
    timer_isr_register(TIMER_GROUP_1, TIMER_1, timer_isr, (void*)3, flags, &inth[3]);
    timer_start(TIMER_GROUP_0, TIMER_0);
    timer_start(TIMER_GROUP_0, TIMER_1);
    timer_start(TIMER_GROUP_1, TIMER_0);
    timer_start(TIMER_GROUP_1, TIMER_1);

    for (x=0; x<4; x++) count[x]=0;
    printf("Interrupts allocated: %d (dis) %d %d %d\n",
            esp_intr_get_intno(inth[0]), esp_intr_get_intno(inth[1]),
            esp_intr_get_intno(inth[2]), esp_intr_get_intno(inth[3]));
    printf("Timer values on start: %d %d %d %d\n", count[0], count[1], count[2], count[3]);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    printf("Timer values after 1 sec: %d %d %d %d\n", count[0], count[1], count[2], count[3]);
    TEST_ASSERT(count[0]==0);
    TEST_ASSERT(count[1]!=0);
    TEST_ASSERT(count[2]!=0);
    TEST_ASSERT(count[3]!=0);

    printf("Disabling timers 1 and 2...\n");
    esp_intr_enable(inth[0]);
    esp_intr_disable(inth[1]);
    esp_intr_disable(inth[2]);
    for (x=0; x<4; x++) count[x]=0;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    printf("Timer values after 1 sec: %d %d %d %d\n", count[0], count[1], count[2], count[3]);
    TEST_ASSERT(count[0]!=0);
    TEST_ASSERT(count[1]==0);
    TEST_ASSERT(count[2]==0);
    TEST_ASSERT(count[3]!=0);
    printf("Disabling other half...\n");
    esp_intr_enable(inth[1]);
    esp_intr_enable(inth[2]);
    esp_intr_disable(inth[0]);
    esp_intr_disable(inth[3]);
    for (x=0; x<4; x++) count[x]=0;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    printf("Timer values after 1 sec: %d %d %d %d\n", count[0], count[1], count[2], count[3]);
    TEST_ASSERT(count[0]==0);
    TEST_ASSERT(count[1]!=0);
    TEST_ASSERT(count[2]!=0);
    TEST_ASSERT(count[3]==0);
    printf("Done.\n");
    esp_intr_free(inth[0]);
    esp_intr_free(inth[1]);
    esp_intr_free(inth[2]);
    esp_intr_free(inth[3]);
}