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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callback_call_count ; 
 int callback_called ; 

__attribute__((used)) static void test_callback(void *params, uint32_t select, uint32_t mask, uint32_t value)
{
    ESP_LOGI("test", "test_callback select = %i,  mask = %i, value = %i", select, mask, value);
    callback_called = true;
    callback_call_count++;
}