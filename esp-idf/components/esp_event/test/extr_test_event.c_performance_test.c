#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {double performed; int expected; int /*<<< orphan*/  done; } ;
typedef  TYPE_1__ performance_data_t ;
typedef  double int64_t ;
struct TYPE_8__ {int /*<<< orphan*/ * task; } ;
typedef  TYPE_2__ esp_event_loop_instance_t ;
typedef  scalar_t__ esp_event_loop_handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  task_priority; int /*<<< orphan*/  task_stack_size; int /*<<< orphan*/ * task_name; } ;
typedef  TYPE_3__ esp_event_loop_args_t ;
typedef  int /*<<< orphan*/ * TaskHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int) ; 
 int ESP_OK ; 
 int /*<<< orphan*/  EVENT_DISPATCH ; 
 int /*<<< orphan*/  EVENT_DISPATCH_PSRAM ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,double) ; 
 int TEST_CONFIG_BASES ; 
 int TEST_CONFIG_IDS ; 
 int /*<<< orphan*/  TEST_PERFORMANCE_GREATER_THAN (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  TEST_SETUP () ; 
 int /*<<< orphan*/  TEST_TEARDOWN () ; 
 double esp_event_handler_register_with (scalar_t__,char const*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 double esp_event_loop_create (TYPE_3__*,scalar_t__*) ; 
 double esp_event_loop_delete (scalar_t__) ; 
 double esp_event_post_to (scalar_t__,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double esp_timer_get_time () ; 
 int /*<<< orphan*/  loop_run_task ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int rand () ; 
 TYPE_3__ test_event_get_default_loop_args () ; 
 int /*<<< orphan*/  test_event_performance_handler ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreCreateBinary () ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTaskCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void performance_test(bool dedicated_task)
{
    // rand() seems to do a one-time allocation. Call it here so that the memory it allocates
    // is not counted as a leak.
    unsigned int _rand __attribute__((unused)) = rand();

    TEST_SETUP();

    const char test_base[] = "qwertyuiopasdfghjklzxvbnmmnbvcxzqwertyuiopasdfghjklzxvbnmmnbvcxz";

    #define TEST_CONFIG_BASES  (sizeof(test_base) - 1)
    #define TEST_CONFIG_IDS    (TEST_CONFIG_BASES / 2)

    // Create loop
    esp_event_loop_args_t loop_args = test_event_get_default_loop_args();
    esp_event_loop_handle_t loop;

    if (!dedicated_task) {
        loop_args.task_name = NULL;
    }

    TEST_ASSERT_EQUAL(ESP_OK, esp_event_loop_create(&loop_args, &loop));

    performance_data_t data;

    // Register the handlers
    for (int base = 0; base < TEST_CONFIG_BASES; base++) {
        for (int id = 0; id < TEST_CONFIG_IDS; id++) {
            TEST_ASSERT_EQUAL(ESP_OK, esp_event_handler_register_with(loop, test_base + base, id, test_event_performance_handler, &data));
        }
    }

    TaskHandle_t mtask = NULL;

    if (!dedicated_task) {
        xTaskCreate(loop_run_task, "loop_run", loop_args.task_stack_size, (void*) loop, loop_args.task_priority, &mtask);
    }

    // Perform performance test
    float running_sum = 0;
    float running_count = 0;

    for (int bases = 1; bases <= TEST_CONFIG_BASES; bases *= 2) {
        for (int ids = 1; ids <= TEST_CONFIG_IDS; ids *= 2) {

            data.performed = 0;
            data.expected = bases * ids;
            data.done = xSemaphoreCreateBinary();

            // Generate randomized list of posts
            int post_bases[TEST_CONFIG_BASES];
            int post_ids[TEST_CONFIG_IDS];

            for (int i = 0; i < bases; i++) {
                post_bases[i] = i;
            }

            for (int i = 0; i < ids; i++) {
                post_ids[i] = i;
            }

            for (int i = 0; i < bases; i++) {
                int rand_a  = rand() % bases;
                int rand_b  = rand() % bases;

                int temp = post_bases[rand_a];
                post_bases[rand_a]= post_bases[rand_b];
                post_bases[rand_b] = temp;
            }

            for (int i = 0; i < ids; i++) {
                int rand_a  = rand() % ids;
                int rand_b  = rand() % ids;

                int temp = post_ids[rand_a];
                post_ids[rand_a]= post_ids[rand_b];
                post_ids[rand_b] = temp;
            }

            // Post the events
            int64_t start = esp_timer_get_time();
            for (int base = 0; base < bases; base++) {
                for (int id = 0; id < ids; id++) {
                    TEST_ASSERT_EQUAL(ESP_OK, esp_event_post_to(loop, test_base + post_bases[base], post_ids[id], NULL, 0, portMAX_DELAY));
                }
            }

            xSemaphoreTake(data.done, portMAX_DELAY);
            int64_t elapsed = esp_timer_get_time() - start;

            // Record data
            TEST_ASSERT_EQUAL(data.expected, data.performed);

            running_count++;
            running_sum += data.performed / (elapsed / (1000000.0));

            vSemaphoreDelete(data.done);
        }
    }

    int average = (int) (running_sum / (running_count));

    if (!dedicated_task) {
        ((esp_event_loop_instance_t*) loop)->task = mtask;
    }

    TEST_ASSERT_EQUAL(ESP_OK, esp_event_loop_delete(loop));

    TEST_TEARDOWN();

#ifdef CONFIG_ESP_EVENT_LOOP_PROFILING
    ESP_LOGI(TAG, "events dispatched/second with profiling enabled: %d", average);
    // Enabling profiling will slow down event dispatch, so the set threshold
    // is not valid when it is enabled.
#else
#ifndef CONFIG_SPIRAM
    TEST_PERFORMANCE_GREATER_THAN(EVENT_DISPATCH, "%d", average);
#else
    TEST_PERFORMANCE_GREATER_THAN(EVENT_DISPATCH_PSRAM, "%d", average);
#endif // CONFIG_SPIRAM
#endif // CONFIG_ESP_EVENT_LOOP_PROFILING
}