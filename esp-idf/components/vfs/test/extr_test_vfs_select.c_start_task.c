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
typedef  int /*<<< orphan*/  test_task_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  send_task ; 
 int /*<<< orphan*/  xTaskCreate (int /*<<< orphan*/ ,char*,int,void*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void start_task(const test_task_param_t *test_task_param)
{
    xTaskCreate(send_task, "send_task", 4*1024, (void *) test_task_param, 5, NULL);
}