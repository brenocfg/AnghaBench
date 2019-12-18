#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {void* data; int /*<<< orphan*/  id; int /*<<< orphan*/  base; scalar_t__ data_allocated; scalar_t__ data_set; } ;
typedef  TYPE_1__ esp_event_post_instance_t ;
struct TYPE_9__ {int /*<<< orphan*/  profiling_mutex; } ;
typedef  TYPE_2__ esp_event_loop_instance_t ;
struct TYPE_10__ {int /*<<< orphan*/  time; int /*<<< orphan*/  invoked; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;} ;
typedef  TYPE_3__ esp_event_handler_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*),TYPE_2__*) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_timer_get_time () ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handler_execute(esp_event_loop_instance_t* loop, esp_event_handler_instance_t *handler, esp_event_post_instance_t post)
{
    ESP_LOGD(TAG, "running post %s:%d with handler %p on loop %p", post.base, post.id, handler->handler, loop);

#ifdef CONFIG_ESP_EVENT_LOOP_PROFILING
    int64_t start, diff;
    start = esp_timer_get_time();
#endif
    // Execute the handler
#if CONFIG_ESP_EVENT_POST_FROM_ISR
    void* data_ptr = NULL;

    if (post.data_set) {
        if (post.data_allocated) {
            data_ptr = post.data.ptr;
        } else {
            data_ptr = &post.data.val;
        }
    }

    (*(handler->handler))(handler->arg, post.base, post.id, data_ptr);
#else
    (*(handler->handler))(handler->arg, post.base, post.id, post.data);
#endif

#ifdef CONFIG_ESP_EVENT_LOOP_PROFILING
    diff = esp_timer_get_time() - start;

    xSemaphoreTake(loop->profiling_mutex, portMAX_DELAY);

    handler->invoked++;
    handler->time += diff;

    xSemaphoreGive(loop->profiling_mutex);
#endif
}