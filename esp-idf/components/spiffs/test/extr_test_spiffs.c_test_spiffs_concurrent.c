#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int write; int /*<<< orphan*/  done; int /*<<< orphan*/  result; } ;
typedef  TYPE_1__ read_write_test_arg_t ;
typedef  int /*<<< orphan*/  names ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_1__ READ_WRITE_TEST_ARG_INIT (char*,int) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int portNUM_PROCESSORS ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  read_write_task ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,size_t) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTaskCreatePinnedToCore (int /*<<< orphan*/ *,char*,int,TYPE_1__*,int,int /*<<< orphan*/ *,int const) ; 

void test_spiffs_concurrent(const char* filename_prefix)
{
    char names[4][64];
    for (size_t i = 0; i < 4; ++i) {
        snprintf(names[i], sizeof(names[i]), "%s%d", filename_prefix, i + 1);
        unlink(names[i]);
    }

    read_write_test_arg_t args1 = READ_WRITE_TEST_ARG_INIT(names[0], 1);
    read_write_test_arg_t args2 = READ_WRITE_TEST_ARG_INIT(names[1], 2);

    printf("writing f1 and f2\n");
    const int cpuid_0 = 0;
    const int cpuid_1 = portNUM_PROCESSORS - 1;
    xTaskCreatePinnedToCore(&read_write_task, "rw1", 2048, &args1, 3, NULL, cpuid_0);
    xTaskCreatePinnedToCore(&read_write_task, "rw2", 2048, &args2, 3, NULL, cpuid_1);

    xSemaphoreTake(args1.done, portMAX_DELAY);
    printf("f1 done\n");
    TEST_ASSERT_EQUAL(ESP_OK, args1.result);
    xSemaphoreTake(args2.done, portMAX_DELAY);
    printf("f2 done\n");
    TEST_ASSERT_EQUAL(ESP_OK, args2.result);

    args1.write = false;
    args2.write = false;
    read_write_test_arg_t args3 = READ_WRITE_TEST_ARG_INIT(names[2], 3);
    read_write_test_arg_t args4 = READ_WRITE_TEST_ARG_INIT(names[3], 4);

    printf("reading f1 and f2, writing f3 and f4\n");

    xTaskCreatePinnedToCore(&read_write_task, "rw3", 2048, &args3, 3, NULL, cpuid_1);
    xTaskCreatePinnedToCore(&read_write_task, "rw4", 2048, &args4, 3, NULL, cpuid_0);
    xTaskCreatePinnedToCore(&read_write_task, "rw1", 2048, &args1, 3, NULL, cpuid_0);
    xTaskCreatePinnedToCore(&read_write_task, "rw2", 2048, &args2, 3, NULL, cpuid_1);

    xSemaphoreTake(args1.done, portMAX_DELAY);
    printf("f1 done\n");
    TEST_ASSERT_EQUAL(ESP_OK, args1.result);
    xSemaphoreTake(args2.done, portMAX_DELAY);
    printf("f2 done\n");
    TEST_ASSERT_EQUAL(ESP_OK, args2.result);
    xSemaphoreTake(args3.done, portMAX_DELAY);
    printf("f3 done\n");
    TEST_ASSERT_EQUAL(ESP_OK, args3.result);
    xSemaphoreTake(args4.done, portMAX_DELAY);
    printf("f4 done\n");
    TEST_ASSERT_EQUAL(ESP_OK, args4.result);

    vSemaphoreDelete(args1.done);
    vSemaphoreDelete(args2.done);
    vSemaphoreDelete(args3.done);
    vSemaphoreDelete(args4.done);
}